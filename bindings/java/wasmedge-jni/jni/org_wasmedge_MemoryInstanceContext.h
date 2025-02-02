/* DO NOT EDIT THIS FILE - it is machine generated */
#include <jni.h>
/* Header for class org_wasmedge_MemoryInstanceContext */

#ifndef _Included_org_wasmedge_MemoryInstanceContext
#define _Included_org_wasmedge_MemoryInstanceContext
#ifdef __cplusplus
extern "C" {
#endif
/*
 * Class:     org_wasmedge_MemoryInstanceContext
 * Method:    nativeInit
 * Signature: (Lorg/wasmedge/MemoryTypeContext;)V
 */
JNIEXPORT void JNICALL Java_org_wasmedge_MemoryInstanceContext_nativeInit
  (JNIEnv *, jobject, jobject);

/*
 * Class:     org_wasmedge_MemoryInstanceContext
 * Method:    setData
 * Signature: ([BII)V
 */
JNIEXPORT void JNICALL Java_org_wasmedge_MemoryInstanceContext_setData
  (JNIEnv *, jobject, jbyteArray, jint, jint);

/*
 * Class:     org_wasmedge_MemoryInstanceContext
 * Method:    getData
 * Signature: (II)[B
 */
JNIEXPORT jbyteArray JNICALL Java_org_wasmedge_MemoryInstanceContext_getData
  (JNIEnv *, jobject, jint, jint);

/*
 * Class:     org_wasmedge_MemoryInstanceContext
 * Method:    getPageSize
 * Signature: ()I
 */
JNIEXPORT jint JNICALL Java_org_wasmedge_MemoryInstanceContext_getPageSize
  (JNIEnv *, jobject);

/*
 * Class:     org_wasmedge_MemoryInstanceContext
 * Method:    growPage
 * Signature: (I)V
 */
JNIEXPORT void JNICALL Java_org_wasmedge_MemoryInstanceContext_growPage
  (JNIEnv *, jobject, jint);

/*
 * Class:     org_wasmedge_MemoryInstanceContext
 * Method:    delete
 * Signature: ()V
 */
JNIEXPORT void JNICALL Java_org_wasmedge_MemoryInstanceContext_delete
  (JNIEnv *, jobject);

#ifdef __cplusplus
}
#endif
#endif
