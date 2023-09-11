#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/select.h> 
#include <arpa/inet.h>
#include <netinet/in.h>
#include <unistd.h> 
#include <pthread.h>
#include <string.h>
#include <time.h>

#define HOST "10.109.23.128"
#define SINK 8087
#define SOURCE 8088


struct circular_buffer {
    pthread_mutex_t lock; // acquire lock before reading or writing any block then release
    char* buffer; //total memory for all blocks = block_size * num_blocks
    int block_size; //maximum size of a single block
    int num_blocks; //maximum number of blocks in buffer
    int* block_lengths; //num_blocks sized array containing the length of each block 
    int cur_size; // number of blocks currently used
    int head; //index of the head of the queue in the circular buffer [0:num_blocks - 1]
    int tail; //index of the tail of the queue in the circular buffer [0:num_blocks - 1]
};

//CLE: will be annotated to be on source / green side and not sharable
struct circular_buffer circ_buff = {
    .cur_size = 0,
    .head = 0,
    .tail = 0 
};

struct circular_buffer* cb = &circ_buff;

// Getters

pthread_mutex_t* get_lock() {
    return &cb->lock;
}

char* get_buffer() {
    return cb->buffer;
}

int* get_block_lengths() {
    return cb->block_lengths;
}

int get_block_size() {
    return cb->block_size;
}

int get_num_blocks() {
    return cb->num_blocks;
}

int get_cur_size() {
    return cb->cur_size;
}

int get_head() {
    return cb->head;
}

int get_tail() {
    return cb->tail;
}

// Setters

void set_block_size(int inp) {
    cb->block_size = inp;
}

void set_num_blocks(int inp) {
    cb->num_blocks = inp;
}

void set_cur_size(int inp) {
    cb->cur_size = inp;
}

void set_head(int inp) {
    cb->head = inp;
}

void set_tail(int inp) {
    cb->tail = inp;
}

void init_lock() {
    pthread_mutex_init(get_lock(), NULL); 
}

//CLE: source / green side
void init_buffer() {
    init_lock();
    set_block_size(1024);
    set_num_blocks(64);

    cb->buffer = (char*) malloc(get_num_blocks() * get_block_size() * sizeof(char));
    memset(cb->buffer, 0, get_num_blocks() * get_block_size() * sizeof(char));

    cb->block_lengths = (int*) malloc(get_num_blocks() * sizeof(int));
    memset(cb->block_lengths, 0, get_num_blocks() * sizeof(int));
}


void print_details() {
    printf("details start\n");
    printf("cb pointer: %p\n", cb);
    printf("buffer pointer: %p\n", get_buffer());
    printf("cur_size: %d\n", get_cur_size());
    printf("num_blocks: %d\n", get_num_blocks());
    printf("head: %d\n", get_head());
    printf("tail: %d\n", get_tail());
    printf("block_size: %d\n", get_block_size());
    printf("details end\n");
}

void better_print(char* s, int start, int length) {
    printf("%s called\n", __func__);
    for (int i = start; i < start + length; i++) {
        printf("%c", s[i]);
    }
    printf("\n");
}

void display() {
    // printf("%s called\n", __func__);
    // print_details();

    int i = 0;
    while (i < cb->cur_size) {
        printf("======== Item %d start ========\n", i);
        better_print(get_buffer(), ((get_head() + i) % get_num_blocks()) * get_block_size(), get_block_lengths()[get_head() + i]);
        printf("========= Item %d end =========\n", i);
        i++;
    }
}

//CLE: source / green side
void enqueue(char* input) {
    printf("%s called\n", __func__);
    // print_details();

    pthread_mutex_lock(get_lock());
    if (strlen(input) > get_block_size()) {
        printf("Unable to enqueue input greater than block size %d\n", get_block_size());
    }
    else if (get_cur_size() < get_num_blocks()) {
        get_block_lengths()[get_tail()] = strlen(input);
        strncpy(&get_buffer()[get_tail() * get_block_size()], input, get_block_lengths()[get_tail()]);
        printf("This is added to the buffer: \n");
        better_print(get_buffer(), get_tail() * get_block_size(), get_block_lengths()[get_tail()]);
        set_tail((get_tail() + 1) % get_num_blocks());
        set_cur_size(get_cur_size() + 1);
    }
    else {
        printf("Buffer is full. Input not queued.\n");
    }
    pthread_mutex_unlock(get_lock());
}

//CLE: source / green side
char* pop() {
    printf("%s called\n", __func__);
    pthread_mutex_lock(get_lock());
    if (get_cur_size() == 0) {
        printf("empty pop\n");
        pthread_mutex_unlock(get_lock());
        return "";
    }

    set_cur_size(get_cur_size() - 1);
    char *output = (char*) malloc(get_block_size());
    output = &get_buffer()[get_head() * get_block_size()];
    cb->block_lengths[get_head()] = 0;
    set_head((get_head() + 1) % get_num_blocks());
    printf("popped this %s\n", output);
    pthread_mutex_unlock(get_lock());
    return output;
}

//CLE: source / green side
char* get_message() {
    printf("%s : length of buffer now: %d\n", __func__, get_cur_size());
    char *output = (char*) malloc(get_block_size());
    memset(output, 0, sizeof(output));
    if(get_cur_size() != 0) {
        memset(output, 0, sizeof(output));
        int len = get_block_lengths()[get_head()];
        strncpy(output, pop(), len);
        return output;
    }
    else {
        printf("Tried to get message from an empty buffer\n");
        return "\0";
    }
}

//CLE: source / green side
int get_source_socket() {
    static bool source_init = false;
    static int source_sock = -1;

    if (source_init) {
        return source_sock;
    }

    struct sockaddr_in source_addr;
    source_addr.sin_family = AF_INET;
    source_addr.sin_port = htons(SOURCE);
    source_addr.sin_addr.s_addr = inet_addr(HOST);

    source_sock = socket(AF_INET, SOCK_STREAM, 0);

    if (source_sock == -1) {
        perror("socket");
        exit(1);
    }
    if (connect(source_sock, (struct sockaddr *) &source_addr, sizeof(source_addr)) < 0) {
        perror("connect");
        exit(1);
    }

    source_init = true;
    return source_sock;
}

// On the orange side
int get_sink_socket() {
    static bool sink_init = false;
    static int sink_sock = -1;

    if (sink_init) {
        return sink_sock;
    }

    struct sockaddr_in sink_addr;
    sink_addr.sin_family = AF_INET;
    sink_addr.sin_port = htons(SINK);
    sink_addr.sin_addr.s_addr = inet_addr(HOST);

    sink_sock = socket(AF_INET, SOCK_STREAM, 0);

    if (sink_sock == -1) {
        perror("socket");
        exit(1);
    }
    if (connect(sink_sock, (struct sockaddr *) &sink_addr, sizeof(sink_addr)) < 0) {
        perror("connect");
        exit(1);
    }

    sink_init = true;
    return sink_sock;
}

char* split(char *str, const char *delim)
{
    char *p = strstr(str, delim);
    if (p == NULL) return NULL;     // delimiter not found
    *p = '\0';                      // terminate string after head
    return p + strlen(delim);       // return tail substring
}

void* source_receive() {
    int sock = -1; 
    sock = get_source_socket();
    char server_response[4096];

    char delimiter[] = "ent>";
    char event[1024];
    char* tail;

    while (1) {
        memset(server_response, 0, sizeof(server_response));
        memset(event, 0, sizeof(event));

        if (recv(sock, &server_response, sizeof(server_response), 0) < 0) {
            perror("recv");
            exit(1);
        }
        printf("%s : Received information\n", __func__);
        printf("%s\n", server_response);

        tail = split(server_response, delimiter);
        while (tail) {
        strcpy(event, server_response);
        strcat(event, delimiter);
        enqueue(event);
        strcpy(server_response, tail);
        tail = split(server_response, delimiter);
        }
        usleep(200000);
    }
}

//CLE: on the source / green side
void start_recv_thread() {
    pthread_t id;
    pthread_create(&id, NULL, source_receive, NULL);
    // pthread_join(id, NULL);
}

//CLE: will be on sink / orange side
void update_sink(char* output, int len) {
    if (send(get_sink_socket(), output, len, 0) < 0) {
        perror("send\n");
        exit(1);
    }
}

//CLE: this function makes non-sharable input to sharable return 
char* sanitize(char* input) {
    return input; // can do filtering on input here if needed.
}


// ask if this function could result in a thread issue.
void pop_source_and_update_sink() {
    printf("%s called\n", __func__);
    char output[get_block_size()];
    
    while(1) {
        memset(output, 0, sizeof(output));
        int len = get_block_lengths()[get_head()];
        if (len != 0) {
            printf("Len isnt 0\n");
            strncpy(output, get_message(), len);
            sanitize(output);
            update_sink(output, len);
        }
        usleep(200000);
    }
}

//CLE: source / green side
void shutdown_source() {
    int source_sock = -1;
    if ((source_sock = get_source_socket()) != -1) {
        close(source_sock);
    }

    for (int i = 0; i < cb->num_blocks; i++) {
        memset(&cb->buffer[i * cb->block_size], 0, cb->block_size);
        memset(&cb->block_lengths[i], 0, cb->block_size);
    }
}

//CLE: sink / orange side
void shutdown_sink() {
    int sink_sock = -1;
    if ((sink_sock = get_sink_socket()) != -1) {
        close(sink_sock);
    }
}

void run_tests() {
    FILE* file = fopen("update.xml", "rb");
    char* content = (char*) malloc(582 + 1);
    fread(content, 1, 582, file);

    printf("events begin\n");
    enqueue(content);
    display(cb);
    enqueue("HEHEHEHE");
    enqueue(content);
    enqueue("4444444444444444444");
    enqueue(content);
    display(cb);
    pop();
    pop();
    pop();
    display(cb);
    char* output = (char*) malloc(1024 * sizeof(char));
    strncpy(output, pop(), 582);

    printf("pointer output: %p\n", output);
    printf("this is in pop output %s\n", output);

    memset(output, 0, 1024 * sizeof(char));
    int len = get_block_lengths()[get_head()];
    strncpy(output, get_message(), len);

    printf("pointer get_message output: %p\n", output);
    printf("this is in get_message output %s\n", output);
    pop();
    display(cb);
    // free_cb(buffer);
    printf("pointer output: %p\n", output);
    printf("this is in output %s\n", output);

    printf("end of the program\n");
}

//CLE: init_buffer() on source / green side
//CLE: get_source_socket() on source / green side
//CLE: get_sink_socket() on sink / orange side, called cross domain
//CLE: start_recv_thread() on source / green side
//CLE: pop_source_update_sink() on source side calls update_sink()
//CLE: update_sink() on sink side called cross domain
//CLE: circular buffer is source side not sharable
//CLE: sanitize() makes non-sharable data from circular buffer sharable.
//CLE: shutdown_source() on source / green side
//CLE: shutdown_sink() on sink / orange side, called cross domain
//CLE: main on source side
int main() {    
    init_buffer();
    get_source_socket();
    get_sink_socket();
    start_recv_thread();
    pop_source_and_update_sink();
    shutdown_source();
    shutdown_sink();
    // run_tests();
    return 0;
}