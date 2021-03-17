#ifndef READER_H
    #include "Reader.h"
#endif

#ifndef FIELDS_H
    #define FIELDS_H

    typedef struct {
        unsigned char accessFlags;
        unsigned char name_index;
        unsigned char descriptor_index;
        unsigned char attributes_count;
        attribute_info *attributes;
    } field_info;

field_info *readFields (FILE* fp, int length,cp_info *cp);


#endif