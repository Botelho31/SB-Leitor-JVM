#include "../include/Utils.h"

std::string Utils::getHexadecimalFromByte(char* array, int size){
    std::string hexstring;
    for (int index = 0; index < size; index++){
        char buffer[3];
        sprintf(buffer, "%X", (unsigned char)array[index]);
        hexstring += buffer;
    }
    return hexstring;
}

std::string Utils::hexSubstrByByte(std::string hex,int start,int size){
    std::string substring = hex.substr(start*2,size*2);
    return substring;
}

u1 * Utils::readUTF8 (FILE* fp, int size) {
	std::vector<unsigned char> *ret = new std::vector<unsigned char>(size);

	for (int i = 0; i < size; i++) {
		ret->at(i) = readU1(fp);
	}

	return (u1*)ret;
} 

std::string Utils::showUTF8 (unsigned char * s, int size) 
{
	std::vector<unsigned char> *v = (std::vector<unsigned char> *) s;
	std::string ret = "";
	size = v->size();
	int i = 0;

	while (i < size) {
		if (!(v->at(i) & 0x80)) { //utf8 only with 1 bit
			ret.push_back(v->at(i));
		} else {
			unsigned short auxCurrent;
			if (!(v->at(i+1) & 0x20)) { //utf8 of 2 bytes
				auxCurrent = ((v->at(i) & 0x1f) << 6) + (v->at(i+1) & 0x3f);
			} else { //utf8 of 3 bytes
				auxCurrent = ((v->at(i) & 0xf) << 12) + ((v->at(i+1) & 0x3f) << 6) + (v->at(i+2) & 0x3f);
				i++;
			}
			i++;
			ret.push_back(auxCurrent);
		}
		i++;
	}

	return ret;
}

u2 Utils::readU2 (FILE *fp) {
	unsigned short ret = 0;
	unsigned char aux;

	fread(&ret, 1, 1, fp);
	fread(&aux, 1, 1, fp);

	ret <<= 8;
	ret |= aux;

	return ret;
}

u1 Utils::readU1 (FILE *fp){
	unsigned char ret;

	fread(&ret, 1, 1, fp);

	return ret;
}

u4 Utils::readU4 (FILE *fp){
	unsigned int ret = 0;
	unsigned char aux;

	for (int i=0; i<4; i++) {
		ret <<= 8;
		fread(&aux, 1, 1, fp);
		ret |= aux;
	}

	return ret;
}

long Utils::u4ToLong (ClassLoaderType high, ClassLoaderType low) 
{
	int64_t ret;
	
	ret = (((int64_t) high.U4) << 32) | low.U4;
	
	return ret;
}

double Utils::u4ToDouble (ClassLoaderType high, ClassLoaderType low) 
{
	double ret;
	uint64_t checkBoundaries = u4ToLong(high, low);
	
	if (checkBoundaries == 0x7ff0000000000000L) {
		//return infinity??
	} else if (checkBoundaries == 0xfff0000000000000L) {
		//return negative infinity??
	} else if ((checkBoundaries >= 0x7ff0000000000001L) && (checkBoundaries <= 0x7ffffffffffffL)) {
		//return NaN??
	} else if ((checkBoundaries >= 0xfff0000000000001L) && (checkBoundaries <= 0xffffffffffffffffL)) {
		//return NaN??
	} else {
		int64_t s = ((checkBoundaries >> 63) == 0) ? 1 : -1;
		int64_t e = ((checkBoundaries >> 52) & 0x7ffL);
		int64_t m = (e == 0) ? (checkBoundaries & 0xfffffffffffffL) << 1 : (checkBoundaries & 0xfffffffffffffL) | 0x10000000000000L;
		
		ret = s * m * pow(2, (e-1075));
	}
	
	return ret;
}

float Utils::u4ToFloat (ClassLoaderType in) 
{
	float ret;
	
	int s = ((in.U4 >> 31) == 0) ? 1 : -1;
	int e = ((in.U4 >> 23) & 0xff);
	int m = (e == 0) ? (in.U4 & 0x7fffff) << 1 : (in.U4 & 0x7fffff) | 0x800000;

	ret = s * m * pow(2, (e-150));
		
	return ret;
}


std::string Utils::getMnemonic(int opcode) 
{
  switch(opcode)
  {
    case(0x00): 
      return  "nop";

    case(0x01): 
      return  "aconst_null";

    case(0x02): 
      return  "iconst_m1";

    case(0x03): 
      return  "iconst_0";

    case(0x04): 
      return  "iconst_1";

    case(0x05): 
      return  "iconst_2";

    case(0x06): 
      return  "iconst_3";

    case(0x07): 
      return  "iconst_4";

    case(0x08): 
      return  "iconst_5";

    case(0x09): 
      return  "lconst_0";

    case(0x0a): 
      return  "lconst_1";

    case(0x0b): 
      return  "fconst_0";

    case(0x0c): 
      return  "fconst_1";

    case(0x0d): 
      return  "fconst_2";

    case(0x0e): 
      return  "dconst_0";
    
    case(0x0f): 
      return  "dconst_1";

    case(0x10): 
      return  "bipush";
    
    case(0x11): 
      return  "sipush";

    case(0x12): 
      return  "ldc";
    
    case(0x13): 
      return  "ldc_w";
    
    case(0x14): 
      return  "ldc2_w";
    
    case(0x15):
       return  "iload";
    
    case(0x16):
       return  "lload";
    
    case(0x17):
      return  "fload";
    
    case(0x18):
      return  "dload";
    
    case(0x19):
      return  "aload";
    
    case(0x1a):
      return  "iload_0";
    
    case(0x1b):
      return  "iload_1";
    
    case(0x1c):
      return  "iload_2";
    
    case(0x1d):
      return  "iload_3";
    
    case(0x1e):
      return  "lload_0";
    
    case(0x1f):
      return  "lload_1";
    
    case(0x20):
      return  "lload_2";
    
    case(0x21):
      return  "lload_3";
    
    case(0x22):
      return  "fload_0";
    
    case(0x23):
      return  "fload_1";
    
    case(0x24):
      return  "fload_2";
    
    case(0x25):
      return  "fload_3";
    
    case(0x26):
      return  "dload_0";
    
    case(0x27):
      return  "dload_1";
    
    case(0x28):
      return  "dload_2";
    
    case(0x29):
      return  "dload_3";
    
    case(0x2a):
      return  "aload_0";
    
    case(0x2b):
      return  "aload_1";
    
    case(0x2c):
      return  "aload_2";
    
    case(0x2d):
      return  "aload_3";
    
    case(0x2e):
      return  "iaload";
    
    case(0x2f):
      return  "laload";
    
    case(0x30):
      return  "faload";
    
    case(0x31):
      return  "daload";
    
    case(0x32):
      return  "aaload";
    
    case(0x33):
      return  "baload";
    
    case(0x34):
      return  "caload";
    
    case(0x35):
      return  "saload";
    
    case(0x36):
      return  "istore";
    
    case(0x37):
      return  "lstore";
    
    case(0x38):
      return  "fstore";
    
    case(0x39):
      return  "dstore";
    
    case(0x3a):
      return  "astore";
    
    case(0x3b):
      return  "istore_0";
    
    case(0x3c):
      return  "istore_1";
    
    case(0x3d):
      return  "istore_2";
    
    case(0x3e):
      return  "istore_3";
    
    case(0x3f):
      return  "lstore_0";
    
    case(0x40):
      return  "lstore_1";
    
    case(0x41):
      return  "lstore_2";
    
    case(0x42):
      return  "lstore_3";
    
    case(0x43):
      return  "fstore_0";
    
    case(0x44):
      return  "fstore_1";
    
    case(0x45):
      return  "fstore_2";
    
    case(0x46):
      return  "fstore_3";
    
    case(0x47):
      return  "dstore_0";
    
    case(0x48):
      return  "dstore_1";
    
    case(0x49):
      return  "dstore_2";
    
    case(0x4a):
      return  "dstore_3";
    
    case(0x4b):
      return  "astore_0";
    
    case(0x4c):
      return  "astore_1";
    
    case(0x4d):
      return  "astore_2";
    
    case(0x4e):
      return  "astore_3";
    
    case(0x4f):
      return  "iastore";
    
    case(0x50):
      return  "lastore";
    
    case(0x51):
      return  "fastore";
    
    case(0x52):
      return  "dastore";
    
    case(0x53):
      return  "aastore";
    
    case(0x54):
      return  "bastore";
    
    case(0x55):
      return  "castore";
    
    case(0x56):
      return  "sastore";
    
    case(0x57):
      return  "pop";
    
    case(0x58):
      return  "pop2";
    
    case(0x59):
      return  "dup";
    
    case(0x5a):
      return  "dup_x1";
    
    case(0x5b):
      return  "dup_x2";
    
    case(0x5c):
      return  "dup2";
    
    case(0x5d):
      return  "dup2_x1";
    
    case(0x5e):
      return  "dup2_x2";
    
    case(0x5f):
      return  "swap";
    
    case(0x60):
      return  "iadd";
    
    case(0x61):
      return  "ladd";
    
    case(0x62):
      return  "fadd";
    
    case(0x63):
      return  "dadd";
    
    case(0x64):
      return  "isub";
    
    case(0x65):
      return  "lsub";
    
    case(0x66):
      return  "fsub";
    
    case(0x67):
      return  "dsub";
    
    case(0x68):
      return  "imul";
    
    case(0x69):
      return  "lmul";
    
    case(0x6a):
      return  "fmul";
    
    case(0x6b):
      return  "dmul";
    
    case(0x6c):
      return  "idiv";
    
    case(0x6d):
      return  "ldiv";
    
    case(0x6e):
      return  "fdiv";
    
    case(0x6f):
      return  "ddiv";
    
    case(0x70):
      return  "irem";
    
    case(0x71):
      return  "lrem";
    
    case(0x72):
      return  "frem";
    
    case(0x73):
      return  "drem";
    
    case(0x74):
      return  "ineg";
    
    case(0x75):
      return  "lneg";
    
    case(0x76):
      return  "fneg";
    
    case(0x77):
      return  "dneg";
    
    case(0x78):
      return  "ishl";
    
    case(0x79):
      return  "lshl";
    
    case(0x7a):
      return  "ishr";
    
    case(0x7b):
      return  "lshr";
    
    case(0x7c):
      return  "iushr";
    
    case(0x7d):
      return  "lushr";
    
    case(0x7e):
      return  "iand";
    
    case(0x7f):
      return  "land";
    
    case(0x80):
      return  "ior";
    
    case(0x81):
      return  "lor";
    
    case(0x82):
      return  "ixor";
    
    case(0x83):
      return  "lxor";
    
    case(0x84):
      return  "iinc";
    
    case(0x85):
      return  "i2l";
    
    case(0x86):
      return  "i2f";
    
    case(0x87):
      return  "i2d";
    
    case(0x88):
      return  "l2i";
    
    case(0x89):
      return  "l2f";
    
    case(0x8a):
      return  "l2d";
    
    case(0x8b):
      return  "f2i";
    
    case(0x8c):
      return  "f2l";
    
    case(0x8d):
      return  "f2d";
    
    case(0x8e):
      return  "d2i";
    
    case(0x8f):
      return  "d2l";
    
    case(0x90):
      return  "d2f";
    
    case(0x91):
      return  "i2b";
    
    case(0x92):
      return  "i2c";
    
    case(0x93):
      return  "i2s";
    
    case(0x94):
      return  "lcmp";
    
    case(0x95):
      return  "fcmpl";
    
    case(0x96):
      return  "fcmpg";
    
    case(0x97):
      return  "dcmpl";
    
    case(0x98):
      return  "dcmpg";
    
    case(0x99):
      return  "ifeq";
    
    case(0x9a):
      return  "ifne";
    
    case(0x9b):
      return  "iflt";
    
    case(0x9c):
      return  "ifge";
    
    case(0x9d):
      return  "ifgt";
    
    case(0x9e):
      return  "ifle";
    
    case(0x9f):
      return  "if_icmpeq";
    
    case(0xa0):
      return  "if_icmpne";
    
    case(0xa1):
      return  "if_icmplt";
    
    case(0xa2):
      return  "if_icmpge";
    
    case(0xa3):
      return  "if_icmpgt";
    
    case(0xa4):
      return  "if_icmple";
    
    case(0xa5):
      return  "if_acmpeq";
    
    case(0xa6):
      return  "if_acmpne";
    
    case(0xa7):
      return  "goto";
    
    case(0xa8):
      return  "jsr";
    
    case(0xa9):
      return  "ret";
    
    case(0xaa):
      return  "tableswitch";
    
    case(0xab):
      return  "lookupswitch";
    
    case(0xac):
      return  "ireturn";
    
    case(0xad):
      return  "lreturn";
    
    case(0xae):
      return  "freturn";
    
    case(0xaf):
      return  "dreturn";
    
    case(0xb0):
      return  "areturn";
    
    case(0xb1):
      return  "return";
    
    case(0xb2):
      return  "getstatic";
    
    case(0xb3):
      return  "putstatic";
    
    case(0xb4):
      return  "getfield";
    
    case(0xb5):
      return  "putfield";
    
    case(0xb6):
      return  "invokevirtual";
    
    case(0xb7):
      return  "invokespecial";
    
    case(0xb8):
      return  "invokestatic";
    
    case(0xb9):
      return  "invokeinterface";
    
    case(0xba):
      return  "invokedynamic";
    
    case(0xbb):
      return  "new";
    
    case(0xbc):
      return  "newarray";
    
    case(0xbd):
      return  "anewarray";
    
    case(0xbe):
      return  "arraylength";
    
    case(0xbf):
      return  "athrow";
    
    case(0xc0):
      return  "checkcast";
    
    case(0xc1):
      return  "instanceof";
    
    case(0xc2):
      return  "monitorenter";
    
    case(0xc3):
      return  "monitorexit";
    
    case(0xc4):
      return  "wide";
    
    case(0xc5):
      return  "multianewarray";
    
    case(0xc6):
      return  "ifnull";
    
    case(0xc7):
      return  "ifnonnull";
    
    case(0xc8):
      return  "goto_w";
    
    case(0xc9):
      return  "jsr_w";
    
    case(0xca):
      return  "breakpoint";
    
    case(0xfe):
      return  "impdep1";
    
    case(0xff):
      return  "impdep2";

    default:
      return NULL;
  }
}

uint32_t Utils::getNBytesValue(uint8_t n, unsigned char* code, int* index)
{

  uint32_t value = code[(*index)++];

  for(int i = 1; i < n; i++)
  {
    value = (value << 8) | code[(*index)++]; 
  }

  return value;
}

void Utils::getOpcodeParams(unsigned char* code, int* index)
{
  switch(code[(*index)++])
  {
    case(0x10): //"bipush";
    case(0x15): //"iload";
    case(0x16): //"lload";
    case(0x17): //"fload";
    case(0x18): //"dload";
    case(0x19): //"aload";
    case(0x36): //"istore";
    case(0x37): //"lstore";
    case(0x38): //"fstore";
    case(0x39): //"dstore";
    case(0x3a): //"astore";
    case(0xbc): //"newarray";
    case(0xa9): //"ret";
      std::cout << " " << getNBytesValue(1,code,index);
      break;
    case(0x11): //"sipush";
    case(0x99): //"ifeq";
    case(0x9a): //"ifne";
    case(0x9b): //"iflt";
    case(0x9c): //"ifge";
    case(0x9d): //"ifgt";
    case(0x9e): //"ifle";
    case(0x9f): //"if_icmpeq";
    case(0xa0): //"if_icmpne";
    case(0xa1): //"if_icmplt";
    case(0xa2): //"if_icmpge";
    case(0xa3): //"if_icmpgt";
    case(0xa4): //"if_icmple";
    case(0xa5): //"if_acmpeq";
    case(0xa6): //"if_acmpne";
    case(0xa7): //"goto";
    case(0xa8): //"jsr";    
    case(0xbd): //"anewarray";
    case(0xc0): //"checkcast";
    case(0xc6): //"ifnull";
    case(0xc7): //"ifnonnull";
      std::cout << " " << getNBytesValue(2,code,index);
      break;
    case(0x12): //"ldc";
      std::cout << " #" << getNBytesValue(1,code,index);
      break;
    case(0x13): //"ldc_w";
    case(0x14): //"ldc2_w";
    case(0xb2): //"getstatic";
    case(0xb3): //"putstatic";
    case(0xb4): //"getfield";
    case(0xb5): //"putfield";
    case(0xbb): //"new";
    case(0xb6): //"invokevirtual";
    case(0xb7): //"invokespecial";
    case(0xb8): //"invokestatic";
    case(0xc1): //"instanceof";
      std::cout << " #" << getNBytesValue(2,code,index);
      break;
    case(0x84): //"iinc";
      std::cout << "#" << getNBytesValue(1,code,index);
      std::cout << " " << getNBytesValue(1,code,index);
      break;
    case(0xc5): //"multianewarray";
      std::cout << " " << getNBytesValue(2,code,index);
      std::cout << " " << getNBytesValue(1,code,index);
      break;
    case(0xc8): //"goto_w";
    case(0xc9): //"jsr_w";
      std::cout << " " << getNBytesValue(4,code,index);
      break;
    case(0xb9): //"invokeinterface";
    case(0xba): //"invokedynamic";
      std::cout << " #" << getNBytesValue(2,code,index);
      std::cout << " " << getNBytesValue(1,code,index);
      std::cout << " " << getNBytesValue(1,code,index);
      break;
    case(0xc4): //"wide";
      switch(code[(*index)++])
      {
        case(0x15): //"iload"; 
        case(0x16): //"lload"; 
        case(0x17): //"fload"; 
        case(0x18): //"dload"; 
        case(0x19): //"aload"; 
        case(0x36): //"istore"; 
        case(0x37): //"lstore"; 
        case(0x38): //"fstore"; 
        case(0x39): //"dstore"; 
        case(0x3a): //"astore"; 
        case(0xa9): //"ret"; 
          std::cout << " " << getNBytesValue(2,code,index);
          break;

        case(0x84): //"iinc";
          std::cout << " " << getNBytesValue(2,code,index);
          std::cout << " " << getNBytesValue(2,code,index);
          break;
      }
      break;
    case(0xaa): //"tableswitch";
    {
      if((*index) % 4 != 0)
      {
        (*index) = *index + (4 - (*index % 4));
      }
      uint32_t defaultvalue = getNBytesValue(4,code,index);
      std::cout << " " << defaultvalue;

      uint32_t low = getNBytesValue(4,code,index);
      std::cout << " " << low;

      uint32_t high = getNBytesValue(4,code,index);
      std::cout << " " << high;

      for(int i = 0; (unsigned int) i < high - low + 1; i++)
      {
        std::cout << " " << getNBytesValue(4,code,index); 
      }
    }
    break;
    
    case(0xab): //"lookupswitch";
    {
      if((*index) % 4 != 0)
      {
        (*index) = *index + (4 - (*index % 4));
      }

      std::cout << " " << getNBytesValue(4,code,index);

      uint32_t npairs = getNBytesValue(4,code,index);
      std::cout << " " << npairs; 

      for(int i = 0; (unsigned int) i < npairs; i++)
      {
        std::cout << " " << getNBytesValue(4,code,index);
          
        std::cout << " " << getNBytesValue(4,code,index); 
      }
    }
    break;

  default:
    break;
  }
}