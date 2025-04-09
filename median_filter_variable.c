#include <stdint.h>

// Structure to hold filter state
typedef struct {
    float *buffer;       // Dynamic buffer for samples
    uint8_t windowSize;  // Size of the filter window
    uint8_t index;       // Current position in buffer
} MedianFilter;

// Initialize the filter with custom window size
int medianFilterInit(MedianFilter *filter, uint8_t windowSize) {
    if (windowSize < 3 || windowSize > 255) {  // Reasonable limits
        return -1;  // Error: invalid window size
    }
    
    filter->buffer = (float *)malloc(windowSize * sizeof(float));
    if (filter->buffer == NULL) {
        return -2;  // Error: memory allocation failed
    }
    
    for(uint8_t i = 0; i < windowSize; i++) {
        filter->buffer[i] = 0.0;    // Initialize with zeros
    }
    
    filter->windowSize = windowSize;
    filter->index = 0;
    return 0;  // Success
}

// Free the filter memory
void medianFilterFree(MedianFilter *filter) {
    if (filter->buffer != NULL) {
        free(filter->buffer);
        filter->buffer = NULL;
    }
}

// Add new sample and get median
float medianFilterAdd(MedianFilter *filter, float newSample) {
    float *temp = (float *)malloc(filter->windowSize * sizeof(float));
    uint8_t i, j;
    
    // Add new sample to buffer
    filter->buffer[filter->index] = newSample;
    
    // Increment index with wrap-around
    filter->index = (filter->index + 1) % filter->windowSize;
    
    // Copy buffer to temporary array for sorting
    for(i = 0; i < filter->windowSize; i++) {
        temp[i] = filter->buffer[i];
    }
    
    // Bubble sort the array
    for(i = 0; i < filter->windowSize - 1; i++) {
        for(j = 0; j < filter->windowSize - 1 - i; j++) {
            if(temp[j] > temp[j + 1]) {
                // Swap elements
                float swap = temp[j];
                temp[j] = temp[j + 1];
                temp[j + 1] = swap;
            }
        }
    }
    
    // Calculate median (using multiplication instead of division)
    float median;
	uint8_t mid = filter->windowSize >> 1;  // divide by 2
	
    if (filter->windowSize & 0x1) {
        // Odd number of samples: middle value
        median = temp[mid];  // Multiply instead of divide
    } else {
		// Even number of samples: average of two middle values
        median = (temp[mid - 1] + temp[mid]) * 0.5f;  // Multiply by 0.5 instead of divide by 2
    }
    
    free(temp);
    return median;
}

// Example usage:
/*
int main() {
    MedianFilter filter;
    
    // Initialize with window size of 7
    if (medianFilterInit(&filter, 7) != 0) {
        printf("Filter initialization failed\n");
        return 1;
    }
    
    float samples[] = {1.2, 5.6, 2.3, 8.9, 4.5, 7.8, 3.4};
    for(int i = 0; i < 7; i++) {
        float median = medianFilterAdd(&filter, samples[i]);
        printf("Sample %d, Median: %.2f\n", i, median);
    }
    
    medianFilterFree(&filter);
    return 0;
}
*/