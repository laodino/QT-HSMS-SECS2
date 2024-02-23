#ifndef HSMSSECS2_H
#define HSMSSECS2_H



class HSMSSECS2
{
    struct SECS_CFG
    {
        unsigned int   t3;			// reply timeout. (in millisecond, the same below)
        unsigned int   t5;			// connection separation timeout
        unsigned int   t6;			// control transaction timeout
        unsigned int   t7;			// not selected (connection idle) timeout
        unsigned int   t8;			// network inter-character timeout

        unsigned int   link_test_interval; // in msec, 0 means disabled
        unsigned short local_port;
        unsigned short device_id;

    };

public:
    HSMSSECS2();
};

#endif // HSMSSECS2_H
