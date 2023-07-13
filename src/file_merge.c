#include "../includes/file_merge.h"
#include "../includes/libsys.h"
#include "../includes/libio.h"

void merge_folder(const char *path, int file_type) {
    char dir_path[str_len(path) + 14];
    char *ocr_dirs[OCR_FOLDER_MAX];
    char *ocr_files[OCR_FILE_MAX];

    //char *translation_dirs[TRANSLATION_FOLDER_MAX];
    //char *translation_files[TRANSLATION_FILE_MAX];

    switch (file_type) {
    case OCRModels:
        sys_read_dir(path, DT_DIR, ocr_dirs, OCR_FOLDER_MAX);
        for (short int i = 0; i < OCR_FOLDER_MAX && ocr_dirs[i] != NULL; i++) {
            str_cpy(dir_path, path);
            str_cat(dir_path, ocr_dirs[i]);
            sys_read_dir(dir_path, DT_REG, ocr_files, OCR_FILE_MAX);
        }
        
    case TranslationModels:
        break;
    default:
        break;
    }
    
}


