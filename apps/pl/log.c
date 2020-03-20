/*******************************************************************************
 * Copyright (c) 2019 Perspecta Labs Inc  - All Rights Reserved.
 * Proprietary and confidential. Unauthorized copy or use of this file, via
 * any medium or mechanism is strictly prohibited.
 ******************************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <stdint.h>
#include <string.h>
#include <stdarg.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/time.h>
#include <time.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <pthread.h>

#include <syslog.h>

#include "log.h"

#define LISTEN_PORT_NUMBER          5102
#define NUM_OF_BIND_RETRIES         3
#define INTERVAL_OF_BIND_RETRIES    5
#define MAX_MDM_CLIENTS             3

#define MC_DIR         "/tmp/mc"
#define MC_ARGS        MC_DIR"/args"

static int log_do_color = 0;
static int loglevel = LOG_DEBUG;
static int indent = 0;

static int num_clients = 0;
static struct socket_array {
    int valid;
    int sock;
} clients[MAX_MDM_CLIENTS];

static pthread_mutex_t clients_lock = PTHREAD_MUTEX_INITIALIZER;

//static void forward_log(char *buf);

char*
get_timestamp(struct timeval *new_time, char *timestamp, int len)
{
    struct tm* ptm;

    ptm = localtime(&new_time->tv_sec);
    int ts_len = strftime(timestamp, len, "%Y-%m-%d %H:%M:%S", ptm);
    long milliseconds = new_time->tv_usec / 1000;

    snprintf(timestamp + ts_len, len - ts_len, ".%03ld", milliseconds);

    return timestamp;
}

static void
log_line(const int level, const char *buf)
{
//    char line[DEBUG_BUF_SIZE];

    if (level > loglevel && level > LOG_ERR) {
       return;
    }

    struct timeval now = { 0, 0 };
    gettimeofday(&now, NULL);
    char timestamp[40];

    const char *color_pfx = "", *color_sfx = "";
    const char *time_pfx = "", *time_sfx = color_sfx;
    const char *level_strings[] = {
            "ERROR", "ERROR", "ERROR", "ERROR", "WARN", "NOTE", "INFO", "DEBUG", "TRACE"
    };
    const char *tag = level_strings[level];

    if (log_do_color) {
        color_pfx = "";
        color_sfx = "\33[0m";
        time_pfx = "\e[0;96m";
        time_sfx = color_sfx;

        switch (level) {
        case LOG_EMERG:
            color_pfx = "\e[1;91m"; /* bright + Red */
            break;
        case LOG_ALERT:
            color_pfx = "\e[1;91m"; /* bright + Red */
            break;
        case LOG_CRIT:
            color_pfx = "\e[1;91m"; /* bright + Red */
            break;
        case LOG_ERR:
            color_pfx = "\e[0;91m"; /* bright + Red */
            break;
        case LOG_WARNING:
            color_pfx = "\e[0;95m"; /* Purple */
            break;
        case LOG_NOTICE:
            color_pfx = "\e[0;95m"; /* Purple */
            break;
        case LOG_INFO:
            color_pfx = "\e[0;93m"; /* Yellow */
            break;
        case LOG_DEBUG:
            color_pfx = "\e[1;92m"; /* Green */
             break;
        case LOG_TRACE:
            break;
        }
    }
    fprintf(stderr, "%s%s%s [%-5s] %s%s%s\n", time_pfx, get_timestamp(&now, timestamp, 40), time_sfx,
            tag, color_pfx, buf, color_sfx);
//    sprintf(line, "%s [%-5s] %s\n", get_timestamp(&now, timestamp, 40), tag, buf);
//
//    forward_log(line);
}

void
mc_log(const int level, const char *fmt, ...)
{
    char buf[DEBUG_BUF_SIZE];
    va_list va;

    memset(buf, '\0', DEBUG_BUF_SIZE);

    va_start(va, fmt);
    vsnprintf(buf + indent, DEBUG_BUF_SIZE, fmt, va);
    va_end(va);

//    syslog(level, buf);

//    if (num_clients > 0)
        log_line(level, buf);
}

void
mc_log_indent(const int level, const char *fmt, const char *func, bool entry)
{
    char buf[DEBUG_BUF_SIZE];

    memset(buf, ' ', DEBUG_BUF_SIZE);
    if (entry) {
        snprintf(buf + indent, DEBUG_BUF_SIZE, fmt, func);
        indent += 1;
        if (indent >= DEBUG_BUF_SIZE)
            indent = 0;
    }
    else {
        indent -= 1;
        if (indent < 0)
            indent = 0;
        snprintf(buf + indent, DEBUG_BUF_SIZE, fmt, func);
    }
    log_line(level, buf);
}

void
mc_set_log_level(int level)
{
    loglevel = level;

    setlogmask(LOG_UPTO(level));
}

void
mc_set_log_color(int on)
{
    log_do_color = on;
}

void
mc_setup_log()
{
    mode_t process_mask = umask(0);
    int result_code = mkdir(MC_DIR, S_IRWXU | S_IRWXG | S_IRWXO);
    umask(process_mask);

    if (result_code == -1 && errno != EEXIST) {
        return;
    }

    FILE *fp = fopen(MC_ARGS, "r");
    if (fp == NULL) {
        return;
    }

    int num_items, level, do_color;
    num_items = fscanf(fp,"%d %d", &level, &do_color);
    if (num_items == EOF)
        return;

    if (num_items >= 1)
        loglevel = level;

    if (num_items >= 2)
        log_do_color = do_color;

    openlog("WINT-MG", LOG_CONS | LOG_PID | LOG_NDELAY, LOG_DAEMON);

    fclose(fp);
}

#if 0
static void
forward_log(char *buf)
{
    // don't use mc_log in this function, as it will get into a loop and stack overflows.

    if (buf == NULL) {
        syslog(LOG_WARNING, "MDM (igmp) null log buffer");
        return;
    }

    int i;
    for (i = 0; i < MAX_MDM_CLIENTS; i++) {
        if (!clients[i].valid)
            continue;

        if (send(clients[i].sock, buf, strlen(buf), MSG_NOSIGNAL) < 0) {
            syslog(LOG_CRIT, "MDM (igmp) log forwarding failed to client %d socket %d: %s",
                   i, clients[i].sock, strerror(errno));

            if (pthread_mutex_lock(&clients_lock)) {
                syslog(LOG_ERR, "MDM pthread_mutex_lock error: %s", strerror(errno));
                continue;
            }
            if (clients[i].valid)
                num_clients--;
            clients[i].valid = 0;

            if (pthread_mutex_unlock(&clients_lock))
                syslog(LOG_ERR, "MDM pthread_mutex_unlock error: %s", strerror(errno));
        }
    }
}
#endif

void
handle_conn(int sock)
{
    if (num_clients >= MAX_MDM_CLIENTS) {
        char buf[DEBUG_BUF_SIZE];
        char timestamp[40];
        struct timeval now = { 0, 0 };
        gettimeofday(&now, NULL);
        snprintf(buf, DEBUG_BUF_SIZE, "%s [%d] MDM ERR max connections (%d) reached. No more connections\n",
                get_timestamp(&now, timestamp, 40), 2, MAX_MDM_CLIENTS);
        mc_log(LOG_WARNING, "%s", buf);
        send(sock, buf, strlen(buf), 0);
    }
    else {
        int idx;
        for (idx = 0; idx < MAX_MDM_CLIENTS; idx++)
            if (clients[idx].valid == 0)
                break;
        if (idx == MAX_MDM_CLIENTS) {
            mc_log(LOG_ERR, "MDM could not find an available client socket");
            return;
        }

        if (pthread_mutex_lock(&clients_lock)) {
            mc_log(LOG_ERR, "MDM pthread_mutex_lock error: %s", strerror(errno));
        }
        clients[idx].sock = sock;
        clients[idx].valid = 1;
        num_clients++;
        if (pthread_mutex_unlock(&clients_lock))
            mc_log(LOG_ERR, "MDM pthread_mutex_unlock error: %s", strerror(errno));

        mc_log(LOG_NOTICE, "MDM connected IGMP_PC_P");
        mc_log(LOG_INFO, "client socket %d is allocated slot %d", sock, idx);
    }
}

void *
mdm_thread_main(void * thread_info)
{
    int i, sock, client_sock;
    struct sockaddr_in server, client;
    socklen_t c;
    int bind_retries, so_reuse = 1;

    num_clients = 0;
    for (i = 0; i < MAX_MDM_CLIENTS; i++) {
        clients[i].valid = 0;
    }

    //Create socket
    sock = socket(AF_INET, SOCK_STREAM, 0);
    if (sock == -1) {
        mc_log(LOG_CRIT, "MDM could not create socket: %s", strerror(errno));
        return NULL;
    }
    mc_log(LOG_DEBUG, "MDM socket created.");

    if (setsockopt(sock, SOL_SOCKET, SO_REUSEADDR, &so_reuse, sizeof(so_reuse)) == -1) {
        mc_log(LOG_CRIT, "MDM setsockopt SO_REUSEADDR failed: %s", strerror(errno));
        return NULL;
    }

    //Prepare the sockaddr_in structure
    server.sin_family = AF_INET;
    server.sin_addr.s_addr = INADDR_ANY;
    server.sin_port = htons(LISTEN_PORT_NUMBER); //5111

    //Bind
    bind_retries = NUM_OF_BIND_RETRIES;
    while (--bind_retries) {
        if (bind(sock, (struct sockaddr *) &server, sizeof(server)) < 0) {
            mc_log(LOG_CRIT, "MDM bind failed:%s. Will retry to bind after %d seconds...",
                    INTERVAL_OF_BIND_RETRIES, strerror(errno));
            sleep(INTERVAL_OF_BIND_RETRIES);
        }
        else {
            mc_log(LOG_DEBUG, "MDM bind done.");
            break;
        }
    }
    if (bind_retries == 0) {
        mc_log(LOG_CRIT, "MDM bind failed: %s", strerror(errno));
        return NULL;
    }

    listen(sock, MAX_MDM_CLIENTS); //number of connections that can be waiting

    mc_log(LOG_DEBUG, "MDM accepting incoming connections...");
    c = sizeof(struct sockaddr_in);

    while ((client_sock = accept(sock, (struct sockaddr *) &client, &c))) {
        struct sockaddr_in temp_sa;
        socklen_t len = sizeof(temp_sa);
        if (getsockname(client_sock, (struct sockaddr *) &temp_sa, &len) != -1) {
            mc_log(LOG_NOTICE, "MDM a message is coming in via [%s:%d].", inet_ntoa(temp_sa.sin_addr),
                    (int) ntohs(temp_sa.sin_port));
        }
        mc_log(LOG_DEBUG, "MDM connection accepted.");

        handle_conn(client_sock);
    }
    if (client_sock < 0) {
        mc_log(LOG_CRIT, "MDM accept failed: %s, terminating", strerror(errno));
        close(sock);
        return NULL;
    }
    close(sock);

    return (void*) 0;
}

void
create_MDM_thread()
{
    log_in();

    pthread_t timer_thread;
    int ret = pthread_create(&timer_thread, 0, mdm_thread_main, NULL);
    if (ret < 0) {
        mc_log(LOG_ERR, "MDM timer pthread_create fail : %s", strerror(errno));
        log_out();
        return;
    }

    log_out();
}

