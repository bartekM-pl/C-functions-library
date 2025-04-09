#include <stdint.h>

// Structure to hold Kalman filter state
typedef struct {
    float x;         // Current state estimate
    float p;         // Estimate uncertainty (covariance)
    float q;         // Process noise covariance
    float r;         // Measurement noise covariance
    float k;         // Kalman gain
} KalmanFilter;

// Initialize the filter with custom parameters
int kalmanFilterInit(KalmanFilter *filter, float initialValue, 
                    float initialUncertainty, float processNoise, 
                    float measurementNoise) {
    if (processNoise < 0 || measurementNoise < 0 || initialUncertainty < 0) {
        return -1;  // Error: invalid parameters
    }
    
    filter->x = initialValue;         // Initial state estimate
    filter->p = initialUncertainty;   // Initial uncertainty
    filter->q = processNoise;         // Process noise covariance
    filter->r = measurementNoise;     // Measurement noise covariance
    filter->k = 0.0;                  // Initial gain
    
    return 0;  // Success
}

// Update filter with new measurement and return filtered value
float kalmanFilterUpdate(KalmanFilter *filter, float measurement) {
    // Prediction step
    filter->p = filter->p + filter->q;
    
    // Update step
    filter->k = filter->p / (filter->p + filter->r);    // Kalman gain
    filter->x = filter->x + filter->k * (measurement - filter->x);  // State update
    filter->p = (1.0 - filter->k) * filter->p;          // Uncertainty update
    
    return filter->x;
}

// Example usage:
/*
int main() {
    KalmanFilter filter;
    
    // Initialize: initial value 0, uncertainty 1, process noise 0.1, measurement noise 0.5
    if (kalmanFilterInit(&filter, 0.0, 1.0, 0.1, 0.5) != 0) {
        printf("Filter initialization failed\n");
        return 1;
    }
    
    float measurements[] = {1.2, 1.5, 1.8, 2.0, 1.9, 2.1, 2.3};
    for(int i = 0; i < 7; i++) {
        float filtered = kalmanFilterUpdate(&filter, measurements[i]);
        printf("Measurement: %.2f, Filtered: %.2f\n", 
               measurements[i], filtered);
    }
    
    return 0;
}
*/