// SPDX-License-Identifier: Apache-2.0
// SPDX-FileCopyrightText: 2019-2022 Second State INC

#include "../jni/org_wasmedge_ASTModuleContext.h"
#include "ExportTypeContext.h"
#include "ImportTypeContext.h"
#include "common.h"
#include "jni.h"
#include "wasmedge/wasmedge.h"
#include <stdlib.h>

WasmEdge_ASTModuleContext *getASTModuleContext(JNIEnv *env,
                                               jobject thisObject) {
  if (thisObject == NULL) {
    return NULL;
  }
  return (WasmEdge_ASTModuleContext *)getPointer(env, thisObject);
}

JNIEXPORT jobject JNICALL Java_org_wasmedge_ASTModuleContext_listImports(
    JNIEnv *env, jobject thisObject) {
  WasmEdge_ASTModuleContext *cxt = getASTModuleContext(env, thisObject);
  uint32_t len = WasmEdge_ASTModuleListImportsLength(cxt);

  const WasmEdge_ImportTypeContext **importTypeContext =
      malloc(sizeof(struct WasmEdge_ImportTypeContext *) * len);

  const WasmEdge_ImportTypeContext **pEdgeImportTypeContext =
      malloc(sizeof(struct WasmEdge_ImportTypeContext *) * len);

  WasmEdge_ASTModuleListImports(cxt, pEdgeImportTypeContext, len);

  jobject importList = CreateJavaArrayList(env, len);
  for (int i = 0; i < len; ++i) {

    AddElementToJavaList(
        env, importList,
        createImportTypeContext(env, pEdgeImportTypeContext[i], thisObject));
  }

  return importList;
}

JNIEXPORT jobject JNICALL Java_org_wasmedge_ASTModuleContext_listExports(
    JNIEnv *env, jobject thisObject) {
  WasmEdge_ASTModuleContext *cxt = getASTModuleContext(env, thisObject);
  uint32_t len = WasmEdge_ASTModuleListExportsLength(cxt);

  const WasmEdge_ExportTypeContext **pEdgeExportTypeContext =
      malloc(sizeof(struct WasmEdge_ExportTypeContext *) * len);

  WasmEdge_ASTModuleListExports(cxt, pEdgeExportTypeContext, len);

  jobject exportList = CreateJavaArrayList(env, len);
  for (int i = 0; i < len; ++i) {

    AddElementToJavaList(
        env, exportList,
        createExportTypeContext(env, pEdgeExportTypeContext[i], thisObject));
  }

  return exportList;
}

jobject createAstModuleContext(JNIEnv *env,
                               const WasmEdge_ASTModuleContext *mod) {

  jclass cls = findJavaClass(env, "org/wasmedge/ASTModuleContext");
  jmethodID constructor = findJavaMethod(env, cls, "<init>", "()V");
  jobject obj = (*env)->NewObject(env, cls, constructor);
  setPointer(env, obj, (long)mod);
  return obj;
}

JNIEXPORT void JNICALL
Java_org_wasmedge_ASTModuleContext_delete(JNIEnv *env, jobject thisObject) {
  WasmEdge_ASTModuleContext *mod = getASTModuleContext(env, thisObject);
  WasmEdge_ASTModuleDelete(mod);
}