#include <dlfcn.h>
#include <stdlib.h>

// Camera
#include <cam_intf.h>

#define CAM_LIB_MCT "libmmcamera2_mct.so"
#define CAM_LIB_OEM "liboemcamera.so"

#define PRINT(PARAM_ID, table_ptr)                                                                  \
    blob_pointer = (char*)(get_pointer_of(PARAM_ID, table_ptr)) - (char*)(table_ptr);               \
    oss_pointer = (char*)(POINTER_OF_META(PARAM_ID, table_ptr)) - (char*)(table_ptr);               \
    blob_size = get_size_of(PARAM_ID);                                                              \
    oss_size = SIZE_OF_PARAM(PARAM_ID, table_ptr);                                                  \
    if ((blob_pointer != oss_pointer) || (blob_size != oss_size)) printf("FIXME!!!\n");             \
    printf("BLOB: %s index=%d pointer=%d size=%d\n", #PARAM_ID, PARAM_ID, blob_pointer, blob_size); \
    printf("OSS : %s index=%d pointer=%d size=%d\n", #PARAM_ID, PARAM_ID, oss_pointer, oss_size);

typedef void* (*get_pointer_of_t)(cam_intf_parm_type_t, metadata_buffer_t*);
typedef uint32_t (*get_size_of_t)(cam_intf_parm_type_t);

void* find_library_handle() {
    void* handle;
    handle = dlopen(CAM_LIB_MCT, RTLD_LAZY);
    if (handle) {
        return handle;
    }

    handle = dlopen(CAM_LIB_OEM, RTLD_LAZY);
    if (handle) {
        return handle;
    }

    return NULL;
}

int main() {
    void* handle;
    get_pointer_of_t get_pointer_of;
    get_size_of_t get_size_of;
    metadata_buffer_t* pMetadata = malloc(sizeof(metadata_buffer_t));

    handle = find_library_handle();
    if (!handle) {
        fprintf(stderr, "%s\n", dlerror());
        return 1;
    }

    get_pointer_of = (get_pointer_of_t)dlsym(handle, "get_pointer_of");
    if (!get_pointer_of) {
        fprintf(stderr, "%s\n", dlerror());
        return 1;
    }

    get_size_of = (get_size_of_t)dlsym(handle, "get_size_of");
    if (!get_size_of) {
        fprintf(stderr, "%s\n", dlerror());
        return 1;
    }

    int blob_pointer = 0;
    int oss_pointer = 0;
    int blob_size = 0;
    int oss_size = 0;

    /* INCLUDE() macros from metadata_data_t go after this */

    dlclose(handle);
    return 0;
}
