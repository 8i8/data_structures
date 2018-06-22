/* DS_qsort: generic qsort function. This function avoids stack smashing by way
 * of a heap allocated stack of pointers to the addresses of the data to be
 * sorted. */
void DS_qsort(void *base, size_t nel, size_t width, int (*comp)(const void *, const void *));
