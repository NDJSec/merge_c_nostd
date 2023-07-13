#include "../includes/libsys.h"
#include "../includes/file_merge.h"

int main(void) {
    int OCRModelsErr = sys_mkdir("merge/OCRModels/");
    int TranslationModelsErr = sys_mkdir("merge/TranslationModels/");
    if (OCRModelsErr != 0 || TranslationModelsErr != 0) {
        sys_write("Can't make folders\n");
    }

    const char *ocr_banner = "------------------------------------Merging OCR Models------------------------------------\n";
    const char *translation_banner = "------------------------------------Merging Translation Models------------------------------------\n";

    sys_write(ocr_banner);
    merge_folder("merge/SplitOCRModels/", OCRModels);

    sys_write(translation_banner);
    //DO TRANSLATION MERGE
    return 0;
}

void _start(void) {
    int main_error = main();

    if (main_error != 0) {
        sys_exit(1);
    }
    sys_exit(0);
}


