#include <stdint.h>

// Structure to hold filter state
typedef struct {
    float buffer[10];    // Circular buffer for 10 samples
    uint8_t index;       // Current position in buffer
    float sum;          // Running sum of buffer contents
} MovingAverageFilter;

// Initialize the filter
void movingAverageFilterInit(MovingAverageFilter *filter) {
    for(int i = 0; i < 10; i++) {
        filter->buffer[i] = 0.0;    // Initialize with zeros
    }
    filter->index = 0;
    filter->sum = 0.0;
}

// Add new sample and get moving average - works sample by sample
float movingAverageFilterAdd(MovingAverageFilter *filter, float newSample) {
    // Subtract the oldest sample from sum
    filter->sum -= filter->buffer[filter->index];
    
    // Add new sample to buffer and sum
    filter->buffer[filter->index] = newSample;
    filter->sum += newSample;
    
    // Increment index with wrap-around
    filter->index = (filter->index + 1) % 10;
    
    // Return average
    return filter->sum / 10.0;
}

// Example usage:
/*
int main() {
    MovingAverageFilter filter;
    movingAverageFilterInit(&filter);
    
    // Process samples one by one
    float samples[] = {1.2, 5.6, 2.3, 8.9, 4.5, 7.8, 3.4, 6.7, 9.1, 0.5};
    for(int i = 0; i < 10; i++) {
        float average = movingAverageFilterAdd(&filter, samples[i]);
        printf("Sample %d, Moving Average: %.2f\n", i, average);
    }
    
    return 0;
}
*/