/*******************************************************************************
 * Copyright (c) 2019 Perspecta Labs Inc  - All Rights Reserved.
 * Proprietary and confidential. Unauthorized copy or use of this file, via
 * any medium or mechanism is strictly prohibited.
 ******************************************************************************/
#ifndef _LOG_H_
#define _LOG_H_

#include <syslog.h>
#include <stdint.h>

#define true 1
#define false 0

typedef char bool;

#if 0   // these are from syslog.h
#define LOG_EMERG   0   /* system is unusable */
#define LOG_ALERT   1   /* action must be taken immediately */
#define LOG_CRIT    2   /* critical conditions */
#define LOG_ERR     3   /* error conditions */
#define LOG_WARNING 4   /* warning conditions */
#define LOG_NOTICE  5   /* normal but significant condition */
#define LOG_INFO    6   /* informational */
#define LOG_DEBUG   7   /* debug-level messages */
#endif
#define LOG_NONE   -1
#define LOG_TRACE   8
#define DEBUG_BUF_SIZE   2048

#define log_in(void)\
    {\
        mc_log_indent(LOG_TRACE, "[+%s]", __FUNCTION__, true);\
    }

#define log_out(void)\
    {\
        mc_log_indent(LOG_TRACE, "[-%s]", __FUNCTION__, false);\
    }

void mc_log(const int level, const char *fmt, ...);
void mc_log_indent(const int level, const char *fmt, const char *func, bool entry);
void mc_set_log_level(int level);
void mc_set_log_color(int on);
void mc_setup_log();
char* get_timestamp(struct timeval *new_time, char *timestamp, int len);
void create_MDM_thread(void);

#endif // _LOG_H_
