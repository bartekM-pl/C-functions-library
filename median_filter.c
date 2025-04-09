#include <stdint.h>

// Structure to hold filter state
typedef struct {
    float buffer[10];    // Circular buffer for 10 samples
    uint8_t index;       // Current position in buffer
} MedianFilter;

// Initialize the filter
void medianFilterInit(MedianFilter *filter) {
    for(int i = 0; i < 10; i++) {
        filter->buffer[i] = 0.0;    // Initialize with zeros
    }
    filter->index = 0;
}

// Add new sample and get median - works sample by sample
float medianFilterAdd(MedianFilter *filter, float newSample) {
    float temp[10];
    int i, j;
    
    // Add new sample to buffer
    filter->buffer[filter->index] = newSample;
    
    // Increment index with wrap-around
    filter->index = (filter->index + 1) % 10;
    
    // Copy buffer to temporary array for sorting
    for(i = 0; i < 10; i++) {
        temp[i] = filter->buffer[i];
    }
    
    // Bubble sort the array
    for(i = 0; i < 9; i++) {
        for(j = 0; j < 9 - i; j++) {
            if(temp[j] > temp[j + 1]) {
                // Swap elements
                float swap = temp[j];
                temp[j] = temp[j + 1];
                temp[j + 1] = swap;
            }
        }
    }
    
    // Return median (average of 5th and 6th elements)
    return (temp[4] + temp[5]) / 2.0;
}

// Example usage:
/*
int main() {
    MedianFilter filter;
    medianFilterInit(&filter);
    
    // Process samples one by one
    float samples[] = {1.2, 5.6, 2.3, 8.9, 4.5, 7.8, 3.4, 6.7, 9.1, 0.5};
    for(int i = 0; i < 10; i++) {
        float median = medianFilterAdd(&filter, samples[i]);
        printf("Sample %d, Median: %.2f\n", i, median);
    }
    
    return 0;
}
*/