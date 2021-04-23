#ifndef JAVA_H
    #include "JavaClass.h"
#endif

#ifndef FRAME_H
#define FRAME_H

class FrameStack;

#include "PilhaOperandos.h"
#include "LocalVariables.h"
#include "Types.h"
#include "Operacoes.h"
#include "Attributes.h"
#include "MethodArea.h"
#include "Method.h"
#include "ConstantPool.h"

typedef struct frame_s{
	unsigned char *pc;
	ConstantPool *cp;	
	PilhaOperandos *operandos;
	LocalVariables *locals;
	Method *m;
} frame;

class FrameStack {
    public:
        FrameStack (JavaClass*);
        void setArguments(std::vector<typedElement>);
        void execute();
        void addFrame(Method, ConstantPool*);
        void addFrame(Method*, ConstantPool*);
        void pop();
    private:
        std::stack<frame*> threads;
        bool nextInstruction();
        int opcode;
        void startPC(frame*);
};

#endif
