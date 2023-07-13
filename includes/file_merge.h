#ifndef FILE_MERGE_H
#define FILE_MERGE_H

#define OCRModels               0
#define TranslationModels       1

#define OCR_FOLDER_MAX          16
#define OCR_FILE_MAX            7
#define TRANSLATION_FOLDER_MAX  60
#define TRANSLATION_FILE_MAX    3

void merge_folder(const char *path, int file_type);

#endif