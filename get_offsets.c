#include <stdlib.h>
#include <dlfcn.h>
#include <cam_intf.h>

#define CAM_LIB_MCT "libmmcamera2_mct.so"
#define CAM_LIB_OEM "liboemcamera.so"

#define PRINT(PARAM_ID, table_ptr)  \
	blob_pointer = (char*)(get_pointer_of(PARAM_ID, table_ptr))-(char*)(table_ptr); \
	oss_pointer = (char*)(POINTER_OF_META(PARAM_ID, table_ptr))-(char*)(table_ptr); \
	blob_size=get_size_of(PARAM_ID); \
	oss_size=SIZE_OF_PARAM(PARAM_ID, table_ptr); \
	if ((blob_pointer != oss_pointer) || (blob_size != oss_size) ) \
		printf("FIXME!!!\n"); \
	printf("BLOB: %s index=%d pointer=%d size=%d\n", #PARAM_ID, PARAM_ID, blob_pointer, blob_size); \
        printf("OSS : %s index=%d pointer=%d size=%d\n", #PARAM_ID, PARAM_ID, oss_pointer, oss_size); 


typedef void* (*get_pointer_of_t)(cam_intf_parm_type_t, metadata_buffer_t*);
typedef uint32_t (*get_size_of_t)(cam_intf_parm_type_t);

void* find_library_handle() {
    void *handle;
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
    void *handle;
    get_pointer_of_t get_pointer_of;
    get_size_of_t get_size_of;
    metadata_buffer_t *pMetadata=malloc(sizeof(metadata_buffer_t));

    handle = find_library_handle();
    if (!handle) {
        fprintf(stderr, "%s\n", dlerror());
        return 1;
    }

    get_pointer_of = (get_pointer_of_t) dlsym(handle, "get_pointer_of");
    if (!get_pointer_of)  {
        fprintf(stderr, "%s\n", dlerror());
        return 1;
    }
    get_size_of = (get_size_of_t) dlsym(handle, "get_size_of");
    if (!get_size_of)  {
        fprintf(stderr, "%s\n", dlerror());
        return 1;
    }
    int blob_pointer=0;
    int oss_pointer=0;
    int blob_size=0;
    int oss_size=0;

    PRINT(CAM_INTF_META_HISTOGRAM,              pMetadata);
    PRINT(CAM_INTF_META_FACE_DETECTION,         pMetadata);
    PRINT(CAM_INTF_META_FACE_RECOG,             pMetadata);
    PRINT(CAM_INTF_META_FACE_BLINK,             pMetadata);
    PRINT(CAM_INTF_META_FACE_GAZE,              pMetadata);
    PRINT(CAM_INTF_META_FACE_SMILE,             pMetadata);
    PRINT(CAM_INTF_META_FACE_LANDMARK,          pMetadata);
    PRINT(CAM_INTF_META_FACE_CONTOUR,           pMetadata);
    PRINT(CAM_INTF_META_AUTOFOCUS_DATA,         pMetadata);

    PRINT(CAM_INTF_META_CDS_DATA,               pMetadata);
    PRINT(CAM_INTF_PARM_UPDATE_DEBUG_LEVEL,     pMetadata);

    /* Specific to HAl1 */
    PRINT(CAM_INTF_META_CROP_DATA,              pMetadata);
    PRINT(CAM_INTF_META_PREP_SNAPSHOT_DONE,     pMetadata);
    PRINT(CAM_INTF_META_GOOD_FRAME_IDX_RANGE,   pMetadata);
    PRINT(CAM_INTF_META_ASD_HDR_SCENE_DATA,     pMetadata);
    PRINT(CAM_INTF_META_ASD_SCENE_INFO,         pMetadata);
    PRINT(CAM_INTF_META_CURRENT_SCENE,          pMetadata);
    PRINT(CAM_INTF_META_AWB_INFO,               pMetadata);
    PRINT(CAM_INTF_META_FOCUS_POSITION,         pMetadata);
    PRINT(CAM_INTF_META_CHROMATIX_LITE_ISP,     pMetadata);
    PRINT(CAM_INTF_META_CHROMATIX_LITE_PP,      pMetadata);
    PRINT(CAM_INTF_META_CHROMATIX_LITE_AE,      pMetadata);
    PRINT(CAM_INTF_META_CHROMATIX_LITE_AWB,     pMetadata);
    PRINT(CAM_INTF_META_CHROMATIX_LITE_AF,      pMetadata);
    PRINT(CAM_INTF_META_CHROMATIX_LITE_ASD,     pMetadata);
    PRINT(CAM_INTF_BUF_DIVERT_INFO,             pMetadata);

    /* Specific to HAL3 */
    PRINT(CAM_INTF_META_FRAME_NUMBER_VALID,     pMetadata);
    PRINT(CAM_INTF_META_URGENT_FRAME_NUMBER_VALID,pMetadata);
    PRINT(CAM_INTF_META_FRAME_DROPPED,          pMetadata);
    PRINT(CAM_INTF_META_FRAME_NUMBER,           pMetadata);
    PRINT(CAM_INTF_META_URGENT_FRAME_NUMBER,    pMetadata);
    PRINT(CAM_INTF_META_COLOR_CORRECT_MODE,     pMetadata);
    PRINT(CAM_INTF_META_COLOR_CORRECT_TRANSFORM,pMetadata);
    PRINT(CAM_INTF_META_COLOR_CORRECT_GAINS,    pMetadata);
    PRINT(CAM_INTF_META_PRED_COLOR_CORRECT_TRANSFORM, pMetadata);
    PRINT(CAM_INTF_META_PRED_COLOR_CORRECT_GAINS, pMetadata);
    PRINT(CAM_INTF_META_AEC_ROI,                pMetadata);
    PRINT(CAM_INTF_META_AEC_STATE,              pMetadata);
    PRINT(CAM_INTF_PARM_FOCUS_MODE,             pMetadata);
    PRINT(CAM_INTF_PARM_MANUAL_FOCUS_POS,       pMetadata);
    PRINT(CAM_INTF_META_AF_ROI,                 pMetadata);
    PRINT(CAM_INTF_META_AF_STATE,               pMetadata);
    PRINT(CAM_INTF_PARM_WHITE_BALANCE,          pMetadata);
    PRINT(CAM_INTF_META_AWB_REGIONS,            pMetadata);
    PRINT(CAM_INTF_META_AWB_STATE,              pMetadata);
    PRINT(CAM_INTF_META_BLACK_LEVEL_LOCK,       pMetadata);
    PRINT(CAM_INTF_META_MODE,                   pMetadata);
    PRINT(CAM_INTF_META_EDGE_MODE,              pMetadata);
    PRINT(CAM_INTF_META_FLASH_POWER,            pMetadata);
    PRINT(CAM_INTF_META_FLASH_FIRING_TIME,      pMetadata);
    PRINT(CAM_INTF_META_FLASH_MODE,             pMetadata);
    PRINT(CAM_INTF_META_FLASH_STATE,            pMetadata);
    PRINT(CAM_INTF_META_HOTPIXEL_MODE,          pMetadata);
    PRINT(CAM_INTF_META_LENS_APERTURE,          pMetadata);
    PRINT(CAM_INTF_META_LENS_FILTERDENSITY,     pMetadata);
    PRINT(CAM_INTF_META_LENS_FOCAL_LENGTH,      pMetadata);
    PRINT(CAM_INTF_META_LENS_FOCUS_DISTANCE,    pMetadata);
    PRINT(CAM_INTF_META_LENS_FOCUS_RANGE,       pMetadata);
    PRINT(CAM_INTF_META_LENS_STATE,             pMetadata);
    PRINT(CAM_INTF_META_LENS_OPT_STAB_MODE,     pMetadata);
    PRINT(CAM_INTF_META_VIDEO_STAB_MODE,        pMetadata);
//    PRINT(CAM_INTF_META_LENS_FOCUS_STATE,       pMetadata); //NOTFOUND
    PRINT(CAM_INTF_META_NOISE_REDUCTION_MODE,   pMetadata);
    PRINT(CAM_INTF_META_NOISE_REDUCTION_STRENGTH, pMetadata);
    PRINT(CAM_INTF_META_SCALER_CROP_REGION,     pMetadata);
    PRINT(CAM_INTF_META_SCENE_FLICKER,          pMetadata);
    PRINT(CAM_INTF_META_SENSOR_EXPOSURE_TIME,   pMetadata);
    PRINT(CAM_INTF_META_SENSOR_FRAME_DURATION,  pMetadata);
    PRINT(CAM_INTF_META_SENSOR_SENSITIVITY,     pMetadata);
    PRINT(CAM_INTF_META_SENSOR_TIMESTAMP,       pMetadata);
    PRINT(CAM_INTF_META_SENSOR_ROLLING_SHUTTER_SKEW, pMetadata);
    PRINT(CAM_INTF_META_SHADING_MODE,           pMetadata);
    PRINT(CAM_INTF_META_STATS_FACEDETECT_MODE,  pMetadata);
    PRINT(CAM_INTF_META_STATS_HISTOGRAM_MODE,   pMetadata);
    PRINT(CAM_INTF_META_STATS_SHARPNESS_MAP_MODE,  pMetadata);
    PRINT(CAM_INTF_META_STATS_SHARPNESS_MAP,   pMetadata);
    PRINT(CAM_INTF_META_TONEMAP_CURVES,        pMetadata);
    PRINT(CAM_INTF_META_LENS_SHADING_MAP,      pMetadata);
    PRINT(CAM_INTF_META_AEC_INFO,               pMetadata);
    PRINT(CAM_INTF_META_SENSOR_INFO,           pMetadata);

    PRINT(CAM_INTF_META_EXIF_DEBUG_AE,        pMetadata);
    PRINT(CAM_INTF_META_EXIF_DEBUG_AWB,       pMetadata);
    PRINT(CAM_INTF_META_EXIF_DEBUG_AF,        pMetadata);
    PRINT(CAM_INTF_META_EXIF_DEBUG_ASD,       pMetadata);
    PRINT(CAM_INTF_META_EXIF_DEBUG_STATS,      pMetadata);
    PRINT(CAM_INTF_PARM_EFFECT,               pMetadata);
    /* Defining as int32_t so that this array is 4 byte aligned */
    PRINT(CAM_INTF_META_PRIVATE_DATA,         pMetadata);

    /* Following are Params only and not metadata currently */
    PRINT(CAM_INTF_PARM_HAL_VERSION,                 pMetadata);
    /* Shared between HAL1 and HAL3 */
    PRINT(CAM_INTF_PARM_ANTIBANDING,                pMetadata);
    PRINT(CAM_INTF_PARM_EXPOSURE_COMPENSATION,       pMetadata);
    PRINT(CAM_INTF_PARM_EV_STEP,                   pMetadata);
    PRINT(CAM_INTF_PARM_AEC_LOCK,                   pMetadata);
    PRINT(CAM_INTF_PARM_FPS_RANGE,                 pMetadata);
    PRINT(CAM_INTF_PARM_AWB_LOCK,                   pMetadata);
    PRINT(CAM_INTF_PARM_BESTSHOT_MODE,             pMetadata);
    PRINT(CAM_INTF_PARM_DIS_ENABLE,                pMetadata);
    PRINT(CAM_INTF_PARM_LED_MODE,                  pMetadata);
    PRINT(CAM_INTF_META_LED_MODE_OVERRIDE,         pMetadata);

    /* dual camera specific params */
    PRINT(CAM_INTF_PARM_RELATED_SENSORS_CALIBRATION, pMetadata);
    PRINT(CAM_INTF_META_AF_FOCAL_LENGTH_RATIO,        pMetadata);
    PRINT(CAM_INTF_META_SNAP_CROP_INFO_SENSOR,       pMetadata);
    PRINT(CAM_INTF_META_SNAP_CROP_INFO_CAMIF,       pMetadata);
    PRINT(CAM_INTF_META_SNAP_CROP_INFO_ISP,         pMetadata);
    PRINT(CAM_INTF_META_SNAP_CROP_INFO_CPP,          pMetadata);
    PRINT(CAM_INTF_META_DCRF,                        pMetadata);

    /* HAL1 specific */
    /* read only */
    PRINT(CAM_INTF_PARM_QUERY_FLASH4SNAP,      pMetadata);
    PRINT(CAM_INTF_PARM_EXPOSURE,               pMetadata);
    PRINT(CAM_INTF_PARM_SHARPNESS,              pMetadata);
    PRINT(CAM_INTF_PARM_CONTRAST,               pMetadata);
    PRINT(CAM_INTF_PARM_SATURATION,               pMetadata);
    PRINT(CAM_INTF_PARM_BRIGHTNESS,              pMetadata);
    PRINT(CAM_INTF_PARM_ISO,                         pMetadata);
    PRINT(CAM_INTF_PARM_EXPOSURE_TIME,           pMetadata);
    PRINT(CAM_INTF_PARM_ZOOM,                       pMetadata);
    PRINT(CAM_INTF_PARM_ROLLOFF,                 pMetadata);
    PRINT(CAM_INTF_PARM_MODE,                    pMetadata);
    PRINT(CAM_INTF_PARM_AEC_ALGO_TYPE,          pMetadata);
    PRINT(CAM_INTF_PARM_FOCUS_ALGO_TYPE,           pMetadata);
    PRINT(CAM_INTF_PARM_AEC_ROI,                   pMetadata);
    PRINT(CAM_INTF_PARM_AF_ROI,                   pMetadata);
    PRINT(CAM_INTF_PARM_SCE_FACTOR,                pMetadata);
    PRINT(CAM_INTF_PARM_FD,                         pMetadata);
    PRINT(CAM_INTF_PARM_MCE,                        pMetadata);
    PRINT(CAM_INTF_PARM_HFR,                        pMetadata);
    PRINT(CAM_INTF_PARM_REDEYE_REDUCTION,          pMetadata);
    PRINT(CAM_INTF_PARM_WAVELET_DENOISE,          pMetadata);
    PRINT(CAM_INTF_PARM_TEMPORAL_DENOISE,         pMetadata);
    PRINT(CAM_INTF_PARM_HISTOGRAM,                 pMetadata);
    PRINT(CAM_INTF_PARM_ASD_ENABLE,                pMetadata);
    PRINT(CAM_INTF_PARM_RECORDING_HINT,            pMetadata);
    PRINT(CAM_INTF_PARM_HDR,                       pMetadata);
    PRINT(CAM_INTF_PARM_FRAMESKIP,                 pMetadata);
    PRINT(CAM_INTF_PARM_ZSL_MODE,                 pMetadata);
    PRINT(CAM_INTF_PARM_HDR_NEED_1X,              pMetadata);
    PRINT(CAM_INTF_PARM_LOCK_CAF,                  pMetadata);
    PRINT(CAM_INTF_PARM_VIDEO_HDR,                 pMetadata);
    PRINT(CAM_INTF_PARM_SENSOR_HDR,                pMetadata);
    PRINT(CAM_INTF_PARM_VT,                        pMetadata);
    PRINT(CAM_INTF_PARM_SET_AUTOFOCUSTUNING,      pMetadata);
    PRINT(CAM_INTF_PARM_SET_VFE_COMMAND,          pMetadata);
    PRINT(CAM_INTF_PARM_SET_PP_COMMAND,           pMetadata);
    PRINT(CAM_INTF_PARM_MAX_DIMENSION,           pMetadata);
    PRINT(CAM_INTF_PARM_RAW_DIMENSION,           pMetadata);
    PRINT(CAM_INTF_PARM_TINTLESS,               pMetadata);
    PRINT(CAM_INTF_PARM_WB_MANUAL,             pMetadata);
    PRINT(CAM_INTF_PARM_CDS_MODE,               pMetadata);
    PRINT(CAM_INTF_PARM_EZTUNE_CMD,               pMetadata);
    PRINT(CAM_INTF_PARM_INT_EVT,                  pMetadata);
    PRINT(CAM_INTF_PARM_RDI_MODE,                 pMetadata);
    PRINT(CAM_INTF_PARM_BURST_NUM,                pMetadata);
    PRINT(CAM_INTF_PARM_RETRO_BURST_NUM,          pMetadata);
    PRINT(CAM_INTF_PARM_BURST_LED_ON_PERIOD,      pMetadata);
    PRINT(CAM_INTF_PARM_LONGSHOT_ENABLE,          pMetadata);
    PRINT(CAM_INTF_PARM_TONE_MAP_MODE,            pMetadata);
    PRINT(CAM_INTF_META_TOUCH_AE_RESULT,          pMetadata);
    PRINT(CAM_INTF_PARM_DUAL_LED_CALIBRATION,     pMetadata);
    PRINT(CAM_INTF_PARM_ADV_CAPTURE_MODE,         pMetadata);

    /* HAL3 specific */
    PRINT(CAM_INTF_META_STREAM_INFO,               pMetadata);
    PRINT(CAM_INTF_META_AEC_MODE,                  pMetadata);
    PRINT(CAM_INTF_META_AEC_PRECAPTURE_TRIGGER,    pMetadata);
    PRINT(CAM_INTF_META_AF_TRIGGER,                pMetadata);
    PRINT(CAM_INTF_META_CAPTURE_INTENT,            pMetadata);
    PRINT(CAM_INTF_META_DEMOSAIC,                  pMetadata);
    PRINT(CAM_INTF_META_SHARPNESS_STRENGTH,        pMetadata);
    PRINT(CAM_INTF_META_GEOMETRIC_MODE,           pMetadata);
    PRINT(CAM_INTF_META_GEOMETRIC_STRENGTH,         pMetadata);
    PRINT(CAM_INTF_META_LENS_SHADING_MAP_MODE,     pMetadata);
    PRINT(CAM_INTF_META_SHADING_STRENGTH,          pMetadata);
    PRINT(CAM_INTF_META_TONEMAP_MODE,              pMetadata);
    PRINT(CAM_INTF_META_STREAM_ID,                 pMetadata);
    PRINT(CAM_INTF_PARM_STATS_DEBUG_MASK,           pMetadata);
    PRINT(CAM_INTF_PARM_STATS_AF_PAAF,             pMetadata);
    PRINT(CAM_INTF_PARM_FOCUS_BRACKETING,         pMetadata);
    PRINT(CAM_INTF_PARM_FLASH_BRACKETING,          pMetadata);
    PRINT(CAM_INTF_META_JPEG_GPS_COORDINATES,      pMetadata);
    PRINT(CAM_INTF_META_JPEG_GPS_PROC_METHODS,      pMetadata);
    PRINT(CAM_INTF_META_JPEG_GPS_TIMESTAMP,         pMetadata);
    PRINT(CAM_INTF_META_JPEG_ORIENTATION,          pMetadata);
    PRINT(CAM_INTF_META_JPEG_QUALITY,               pMetadata);
    PRINT(CAM_INTF_META_JPEG_THUMB_QUALITY,         pMetadata);
    PRINT(CAM_INTF_META_JPEG_THUMB_SIZE,            pMetadata);
    PRINT(CAM_INTF_META_TEST_PATTERN_DATA,       pMetadata);
    PRINT(CAM_INTF_META_PROFILE_TONE_CURVE,         pMetadata);
    PRINT(CAM_INTF_META_OTP_WB_GRGB,               pMetadata);
    PRINT(CAM_INTF_META_IMG_HYST_INFO,             pMetadata);
    PRINT(CAM_INTF_META_CAC_INFO,                 pMetadata);
    PRINT(CAM_INTF_PARM_CAC,                       pMetadata);
    PRINT(CAM_INTF_META_NEUTRAL_COL_POINT,         pMetadata);
    PRINT(CAM_INTF_PARM_ROTATION,                  pMetadata);
    PRINT(CAM_INTF_PARM_HW_DATA_OVERWRITE,        pMetadata);
    PRINT(CAM_INTF_META_IMGLIB,                    pMetadata);
    PRINT(CAM_INTF_PARM_CAPTURE_FRAME_CONFIG,       pMetadata);
    PRINT(CAM_INTF_PARM_CUSTOM,                     pMetadata);
    PRINT(CAM_INTF_PARM_FLIP,                     pMetadata);
    PRINT(CAM_INTF_META_USE_AV_TIMER,               pMetadata);
    PRINT(CAM_INTF_META_EFFECTIVE_EXPOSURE_FACTOR,  pMetadata);
    PRINT(CAM_INTF_META_LDAF_EXIF,                  pMetadata);
    PRINT(CAM_INTF_META_BLACK_LEVEL_SOURCE_PATTERN,  pMetadata);
    PRINT(CAM_INTF_META_BLACK_LEVEL_APPLIED_PATTERN, pMetadata);
    PRINT(CAM_INTF_META_LOW_LIGHT,                   pMetadata);
    PRINT(CAM_INTF_META_IMG_DYN_FEAT,            pMetadata);
    PRINT(CAM_INTF_PARM_MANUAL_CAPTURE_TYPE,         pMetadata);
    PRINT(CAM_INTF_AF_STATE_TRANSITION,              pMetadata);
    PRINT(CAM_INTF_PARM_INITIAL_EXPOSURE_INDEX,      pMetadata);
    PRINT(CAM_INTF_PARM_INSTANT_AEC,                pMetadata);
    PRINT(LENOVO1,                              pMetadata);//HACK
    //PRINT(LENOVO2,                             pMetadata);//HACK
    PRINT(LENOVO3, pMetadata);//HACK

    dlclose(handle);
    return 0;
}