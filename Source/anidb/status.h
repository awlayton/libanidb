/*
 *  status.h
 *  libanidb
 *
 *  Created by Andreas Meingast on 25.08.06.
 *  Copyright 2006 Andreas Meingast. All rights reserved.
 *
 *  $Id: status.h 1 2007-03-24 13:06:42Z ameingast $
 *
 */

#ifndef ANI_STATUS_CODES_H
#define ANI_STATUS_CODES_H

#define ANI_STATUS_NO_SERVER_REPLY                          001
#define ANI_STATUS_SEND_FAILED                              002
#define ANI_STATUS_MALFORMED_RESPONSE                       003
#define ANI_STATUS_INTERNAL_ERROR                           004

#define ANI_STATUS_LOGIN_ACCEPTED                           200
#define ANI_STATUS_LOGIN_ACCEPTED_NEW_VERSION               201
#define ANI_STATUS_LOGGED_OUT                               203
#define ANI_STATUS_RESOURCE                                 205
#define ANI_STATUS_STATS                                    206
#define ANI_STATUS_TOP                                      207
#define ANI_STATUS_UPTIME                                   208
#define ANI_STATUS_ENCRYPTION_ENABLED                       209

#define ANI_STATUS_MYLIST_ENTRY_ADDED                       210
#define ANI_STATUS_MYLIST_ENTRY_DELETED                     211

#define ANI_STATUS_ADDED_FILE                               214
#define ANI_STATUS_ADDED_STREAM                             215

#define ANI_STATUS_ENCODING_CHANGED                         219

#define ANI_STATUS_FILE                                     220
#define ANI_STATUS_MYLIST                                   221
#define ANI_STATUS_MYLIST_STATS                             222

#define ANI_STATUS_ANIME                                    230
#define ANI_STATUS_ANIME_BEST_MATCH                         231
#define ANI_STATUS_RANDOMANIME                              232

#define ANI_STATUS_EPISODE                                  240
#define ANI_STATUS_PRODUCER                                 245
#define ANI_STATUS_GROUP                                    250

#define ANI_STATUS_BUDDY_LIST                               253
#define ANI_STATUS_BUDDY_STATE                              254
#define ANI_STATUS_BUDDY_ADDED                              255
#define ANI_STATUS_BUDDY_DELETED                            256
#define ANI_STATUS_BUDDY_ACCEPTED                           257
#define ANI_STATUS_BUDDY_DENIED                             258

#define ANI_STATUS_VOTED                                    260
#define ANI_STATUS_VOTE_FOUND                               261
#define ANI_STATUS_VOTE_UPDATED                             262
#define ANI_STATUS_VOTE_REVOKED                             263

#define ANI_STATUS_NOTIFICATION_ENABLED                     270
#define ANI_STATUS_NOTIFICATION_NOTIFY                      271
#define ANI_STATUS_NOTIFICATION_MESSAGE                     272
#define ANI_STATUS_NOTIFICATION_BUDDY                       273
#define ANI_STATUS_NOTIFICATION_SHUTDOWN                    274
#define ANI_STATUS_PUSHACK_CONFIRMED                        280
#define ANI_STATUS_NOTIFYACK_SUCCESSFUL_M                   281
#define ANI_STATUS_NOTIFYACK_SUCCESSFUL_N                   282
#define ANI_STATUS_NOTIFICATION                             290
#define ANI_STATUS_NOTIFYLIST                               291
#define ANI_STATUS_NOTIFYGET_MESSAGE                        292
#define ANI_STATUS_NOTIFYGET_NOTIFY                         293

#define ANI_STATUS_SENDMSG_SUCCESSFUL                       294
#define ANI_STATUS_USER                                     295

#define ANI_STATUS_PONG                                     300
#define ANI_STATUS_AUTHPONG                                 301
#define ANI_STATUS_NO_SUCH_RESOURCE                         305
#define ANI_STATUS_API_PASSWORD_NOT_DEFINED                 309

#define ANI_STATUS_FILE_ALREADY_IN_MYLIST                   310
#define ANI_STATUS_MYLIST_ENTRY_EDITED                      311
#define ANI_STATUS_MULTIPLE_MYLIST_ENTRIES                  312

#define ANI_STATUS_SIZE_HASH_EXISTS                         314
#define ANI_STATUS_INVALID_DATA                             315
#define ANI_STATUS_STREAMNOID_USED                          316

#define ANI_STATUS_NO_SUCH_FILE                             320
#define ANI_STATUS_NO_SUCH_ENTRY                            321
#define ANI_STATUS_MULTIPLE_FILES_FOUND                     322

#define ANI_STATUS_NO_SUCH_ANIME                            330
#define ANI_STATUS_NO_SUCH_EPISODE                          340
#define ANI_STATUS_NO_SUCH_PRODUCER                         345
#define ANI_STATUS_NO_SUCH_GROUP                            350

#define ANI_STATUS_BUDDY_ALREADY_ADDED                      355
#define ANI_STATUS_NO_SUCH_BUDDY                            356
#define ANI_STATUS_BUDDY_ALREADY_ACCEPTED                   357
#define ANI_STATUS_BUDDY_ALREADY_DENIED                     358

#define ANI_STATUS_NO_SUCH_VOTE                             360
#define ANI_STATUS_INVALID_VOTE_TYPE                        361
#define ANI_STATUS_INVALID_VOTE_VALUE                       362
#define ANI_STATUS_PERMVOTE_NOT_ALLOWED                     363
#define ANI_STATUS_ALREADY_PERMVOTED                        364

#define ANI_STATUS_NOTIFICATION_DISABLED                    370
#define ANI_STATUS_NO_SUCH_PACKET_PENDING                   380
#define ANI_STATUS_NO_SUCH_ENTRY_M                          381
#define ANI_STATUS_NO_SUCH_ENTRY_N                          382

#define ANI_STATUS_NO_SUCH_MESSAGE                          392
#define ANI_STATUS_NO_SUCH_NOTIFY                           393
#define ANI_STATUS_NO_SUCH_USER                             394

#define ANI_STATUS_NOT_LOGGED_IN                            403

#define ANI_STATUS_NO_SUCH_MYLIST_FILE                      410
#define ANI_STATUS_NO_SUCH_MYLIST_ENTRY                     411

#define ANI_STATUS_LOGIN_FAILED                             500
#define ANI_STATUS_LOGIN_FIRST                              501
#define ANI_STATUS_ACCESS_DENIED                            502
#define ANI_STATUS_CLIENT_VERSION_OUTDATED                  503
#define ANI_STATUS_CLIENT_BANNED                            504
#define ANI_STATUS_ILLEGAL_INPUT_OR_ACCESS_DENIED           505
#define ANI_STATUS_INVALID_SESSION                          506
#define ANI_STATUS_NO_SUCH_ENCRYPTION_TYPE                  509
#define ANI_STATUS_ENCODING_NOT_SUPPORTED                   519

#define ANI_STATUS_BANNED                                   555
#define ANI_STATUS_UNKNOWN_COMMAND                          598

#define ANI_STATUS_INTERNAL_SERVER_ERROR                    600
#define ANI_STATUS_OUT_OF_SERVICE                           601
#define ANI_STATUS_SERVER_BUSY                              602
#define ANI_STATUS_API_VIOLATION                            666

#define ANI_STATUS_VERSION                                  998

#endif /* ANI_STATUS_CODES_H */
