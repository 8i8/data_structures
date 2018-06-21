/* DS_Qsort: generic qsort function. This function avoids stack smashing by way
 * of a heap allocated stack of pointers to the addresses of the data to be
 * sorted. */
void DS_Qsort(void *base, size_t nel, size_t width, int (*comp)(const void *, const void *));
