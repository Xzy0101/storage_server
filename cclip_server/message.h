#pragma once

#ifndef CCLIP_MESSAGE_H
#define CCLIP_MESSAGE_H

#include "network.h"
#include "database.h"

#include <vector>
#include <sstream>

using namespace std;

/* length of each field, except data */
#define LEN_HEADER 1
#define LEN_UNAME 17  //including string ending 0
#define LEN_UPASS 65  //including string ending 0
#define LEN_RNUM sizeof(int)
#define LEN_DNAME 49  //including string ending 0
#define LEN_DATA (16*1024*1024)  //Max payload size 16MB

/* Max payload size, plus header and device name. */
#define BUFFER_SIZE (LEN_DATA+LEN_HEADER+LEN_DNAME)

/* Message headers */
#define H_NEW_USER 'N'    //new user      c->s  header + username + password
#define H_LOG_IN 'L'      //user login    c->s  header + username + password
#define H_CHANGE_PASS 'C' //change pass   c->s  header + password
#define H_SYNC_RNUM 'S'   //sync rnum     c->s  header
#define H_ACCEPTED 'A'    //user accepted s->c  header
#define H_RECORD_NUM 'R'  //record number s<->c header + record_number
#define H_RECORD 'M'      //data transfer s<->c header + device_name + data

constexpr char M_ACCEPTED = H_ACCEPTED;

/* log in or create new user */
int client_login(SOCKET client, SSL *ssl, ofstream &lerr, mutex &mtx_errorlog);

#endif