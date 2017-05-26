#include <llvm-c/Core.h>
#include <llvm-c/ExecutionEngine.h>
#include <llvm-c/Target.h>
#include <llvm-c/Analysis.h>
#include <llvm-c/BitWriter.h>

#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>

typedef enum {
    CodeUninitialized,
    CodeEval,
    CodeEnter,
    CodeReturnInt,
} Code;


LLVMTypeRef mkVoidPointerType() {
    return LLVMPointerType(LLVMIntType(8), 0);
}

LLVMTypeRef mkCodeType() {
    static const int nelems = 3;
    LLVMTypeRef elems[] = { LLVMIntType(32), mkVoidPointerType(), mkVoidPointerType() };
    return LLVMStructType(elems, nelems, /*isPacked=*/ 0);
}

LLVMModuleRef mkModule() {
    LLVMModuleRef mod = LLVMModuleCreateWithName("thinair");
    LLVMAddGlobal(mod, mkCodeType(), "g_code");
    return mod;

    /*
    LLVMTypeRef param_types[] = { LLVMInt32Type(), LLVMInt32Type() };
    LLVMTypeRef ret_type = LLVMFunctionType(LLVMInt32Type(), param_types, 2, 0);
    LLVMValueRef sum = LLVMAddFunction(mod, "sum", ret_type);

    LLVMBasicBlockRef entry = LLVMAppendBasicBlock(sum, "entry");

    LLVMBuilderRef builder = LLVMCreateBuilder();
    LLVMPositionBuilderAtEnd(builder, entry);
    LLVMValueRef tmp = LLVMBuildAdd(builder, LLVMGetParam(sum, 0), LLVMGetParam(sum, 1), "tmp");
    LLVMBuildRet(builder, tmp);
    */
}



char* getModuleString(LLVMModuleRef mod) {
  return LLVMPrintModuleToString(mod);
}

