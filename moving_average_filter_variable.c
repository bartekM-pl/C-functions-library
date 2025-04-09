#include <stdint.h>

// Structure to hold filter state
typedef struct {
    float *buffer;       // Dynamic circular buffer
    uint16_t windowSize; // Size of the window
    uint16_t index;      // Current position in buffer
    float sum;          // Running sum of buffer contents
    float invWindowSize; // 1/windowSize for multiplication
} MovingAverageFilter;

// Initialize the filter with custom window size
int movingAverageFilterInit(MovingAverageFilter *filter, uint16_t windowSize) {
    // Check for valid window size
    if (windowSize == 0) {
        return -1;  // Error: invalid window size
    }
    
    // Allocate buffer
    filter->buffer = (float *)malloc(windowSize * sizeof(float));
    if (filter->buffer == NULL) {
        return -2;  // Error: memory allocation failed
    }
    
    // Initialize buffer with zeros
	memset(filter->buffer, 0, windowSize * sizeof(float));
    
    filter->windowSize = windowSize;
    filter->index = 0;
    filter->sum = 0.0f;
    filter->invWindowSize = 1.0f / (float)windowSize;  // Pre-calculate inverse
    
    return 0;  // Success
}

// Free the filter memory
void movingAverageFilterFree(MovingAverageFilter *filter) {
    if (filter->buffer != NULL) {
        free(filter->buffer);
        filter->buffer = NULL;
    }
}

// Add new sample and get moving average
float movingAverageFilterAdd(MovingAverageFilter *filter, float newSample) {
    // Subtract the oldest sample from sum
    filter->sum -= filter->buffer[filter->index];
    
    // Add new sample to buffer and sum
    filter->buffer[filter->index] = newSample;
    filter->sum += newSample;
    
    // Increment index with wrap-around
    filter->index = (filter->index + 1) % filter->windowSize;
    
    // Return average using multiplication
    return filter->sum * filter->invWindowSize;
}

// Example usage:
/*
int main() {
    MovingAverageFilter filter;
    
    // Initialize with window size of 5
    if (movingAverageFilterInit(&filter, 5) != 0) {
        printf("Filter initialization failed\n");
        return 1;
    }
    
    // Process samples one by one
    float samples[] = {1.2, 5.6, 2.3, 8.9, 4.5, 7.8, 3.4};
    for(int i = 0; i < 7; i++) {
        float average = movingAverageFilterAdd(&filter, samples[i]);
        printf("Sample %d, Moving Average: %.2f\n", i, average);
    }
    
    // Clean up
    movingAverageFilterFree(&filter);
    return 0;
}
*/