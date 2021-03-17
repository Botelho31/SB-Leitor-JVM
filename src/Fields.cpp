#include "Fields.h"

field_info *readFields (FILE* fp, int length, cp_info* cp) {
	field_info *ret = (field_info *) malloc(sizeof(field_info) * length);


	for (int i = 0; i < length; i++) {
		ret[i].accessFlags = readU2(fp) & 0X0df;
        ret[i].name_index = readU2(fp);
        ret[i].descriptor_index = readU2(fp);
        ret[i].attributes_count = readU2(fp);
        ret[i].attributes = (attribute_info *) malloc(sizeof(attribute_info) * ret[i].attributes_count);
        for (int j = 0; j < ret[i].attributes_count; j++) {
            ret[i].attributes[j] = readAttribute(fp,cp);
        }
	}
	return ret;
}