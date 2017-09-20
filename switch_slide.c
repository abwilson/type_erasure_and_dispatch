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

