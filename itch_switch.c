This code take from

https://github.com/csinitiative/fhce/blob/master/feeds/itch/multicast/common/fh_itch_parse.c
/*
 * Copyright (C) 2008, 2009, 2010 The Collaborative Software Foundation.
 *
 * This file is part of FeedHandlers (FH).
 *
 * FH is free software: you can redistribute it and/or modify it under the terms of the
 * GNU Lesser General Public License as published by the Free Software Foundation, either version 3
 * of the License, or (at your option) any later version.
 *
 * FH is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without
 * even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public License
 * along with FH.  If not, see <http://www.gnu.org/licenses/>.
 */
    /* read the message type and process the message */
    msg_type = *(char *)buffer;
    switch (msg_type) {

    /* set the millisecond timestamp to seconds * value and remember this value for later */
    case 'T':
        conn->timestamp = fh_itch_parse_atoi(buffer + 1, 5) * 1000;
        break;

    /* subtract the current milliseconds from the timestamp and add the new milliseconds */
    case 'M':
        conn->timestamp -= conn->timestamp % 1000;
        conn->timestamp += fh_itch_parse_atoi(buffer + 1, 3);
        break;

    /* process a system event message */
    case 'S':
        if (fh_itch_parse_sys_msg(buffer, msg_length, conn, &data, &data_length) != FH_OK) {
            return -1;
        }
        break;

    /* process a stock directory message */
    case 'R':
        if (fh_itch_parse_stock_dir_msg(buffer, msg_length, conn, &data, &data_length) != FH_OK) {
            return -1;
        }
        break;

    /* process a stock trading action message */
    case 'H':
        if (fh_itch_parse_stock_trade_act_msg(buffer, msg_length, conn, &data,
                                              &data_length) != FH_OK) {
            return -1;
        }
        break;

    /* process a market participant position message */
    case 'L':
        if (fh_itch_parse_market_part_pos_msg(buffer, msg_length, conn, &data,
                                              &data_length) != FH_OK) {
            return -1;
        }
        break;

    /* process an order add (w/o MPID attribution) message */
    case 'A':
        if (fh_itch_parse_order_add_msg(buffer, msg_length, conn, &data, &data_length) != FH_OK) {
            return -1;
        }
        break;

      /* read the message type and process the message */
    msg_type = *(char *)buffer;
    switch (msg_type) {

    /* set the millisecond timestamp to seconds * value and remember this value for later */
    case 'T':
        conn->timestamp = fh_itch_parse_atoi(buffer + 1, 5) * 1000;
        break;

    /* subtract the current milliseconds from the timestamp and add the new milliseconds */
    case 'M':
        conn->timestamp -= conn->timestamp % 1000;
        conn->timestamp += fh_itch_parse_atoi(buffer + 1, 3);
        break;

    /* process a system event message */
    case 'S':
        if (fh_itch_parse_sys_msg(buffer, msg_length, conn, &data, &data_length) != FH_OK) {
            return -1;
        }
        break;

    /* process a stock directory message */
    case 'R':
        if (fh_itch_parse_stock_dir_msg(buffer, msg_length, conn, &data, &data_length) != FH_OK) {
            return -1;
        }
        break;

    /* process a stock trading action message */
    case 'H':
        if (fh_itch_parse_stock_trade_act_msg(buffer, msg_length, conn, &data,
                                              &data_length) != FH_OK) {
            return -1;
        }
        break;

    /* process a market participant position message */
    case 'L':
        if (fh_itch_parse_market_part_pos_msg(buffer, msg_length, conn, &data,
                                              &data_length) != FH_OK) {
            return -1;
        }
        break;

    /* process an order add (w/o MPID attribution) message */
    case 'A':
        if (fh_itch_parse_order_add_msg(buffer, msg_length, conn, &data, &data_length) != FH_OK) {
            return -1;
        }
        break;

        etc, etc, ...

  
