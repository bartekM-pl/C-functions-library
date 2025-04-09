# Signal Processing Library in C

This repository contains a collection of signal processing functions implemented in C. The library provides efficient and reusable implementations of common filtering algorithms suitable for embedded systems, real-time applications, and general signal processing tasks.

## Features

- **Moving Average Filter**: A sliding window average filter with constant or configurable window size
- **Median Filter**: A sliding window median filter with constant or configurable window size
- **Kalman Filter**: A simple 1D Kalman filter for scalar value filtering
- Modular design with clear initialization and update functions
- Memory management for dynamic allocation where applicable
- Example usage included in code comments

## Installation

Clone the repository:

```bash
git clone https://github.com/bartekM-pl/C-functions-library.git
cd C-functions-library
```

The library consists of header-less C functions that can be directly included in your project. Simply copy the relevant .c files or include them in your build system.

## Usage

See the comments in the source files for detailed example usage and parameter explanations.

## Files

- median_filter.c: Implementation of the sliding window median filter
- median_filter_variable.c: Implementation of the sliding window median filter (variable windows size)
- moving_average_filter.c: Implementation of the sliding window average filter
- moving_average_filter_variable.c: Implementation of the sliding window average filter (variable windows size)
- kalman_filter.c: Implementation of the simple Kalman filter

## API Reference

### Median Filter (variable window) median_filter_variable.c

- int medianFilterInit(MedianFilter *filter, uint8_t windowSize): Initialize with custom window size
- float medianFilterAdd(MedianFilter *filter, float newSample): Add sample and get median
- void medianFilterFree(MedianFilter *filter): Free allocated memory

### Median Filter (constant window) median_filter.c

- int medianFilterInit(MedianFilter *filter): Initialize filter
- float medianFilterAdd(MedianFilter *filter, float newSample): Add sample and get median

### Moving Average Filter (variable window) moving_average_filter_variable.c

- int movingAverageFilterInit(MovingAverageFilter *filter, uint8_t windowSize): Initialize with custom window size
- float movingAverageFilterAdd(MovingAverageFilter *filter, float newSample): Add sample and get median
- void movingAverageFilterFree(MovingAverageFilter *filter): Free allocated memory

### Moving Average Filter (constant window) moving_average_filter.c

- int movingAverageFilterInit(MovingAverageFilter *filter): Initialize filter
- float movingAverageFilterAdd(MovingAverageFilter *filter, float newSample): Add sample and get median

### Kalman Filter kalman_filter.c

- int kalmanFilterInit(KalmanFilter *filter, float initialValue, float initialUncertainty, float processNoise, float measurementNoise): Initialize with parameters
- float kalmanFilterUpdate(KalmanFilter *filter, float measurement): Update with new measurement and get filtered value

## Dependencies
- Standard C library (stdint.h, stdlib.h for malloc/free)

## Contributing
Contributions are welcome! Please:
1. Fork the repository
2. Create a feature branch
3. Submit a pull request with a clear description of changes
Suggestions for new filters or optimizations are appreciated.

## License
This library is licensed under the MIT License. See LICENSE for details.

## Acknowledgments
- Created as part of a collaborative effort to provide open-source signal processing tools
- Inspired by common filtering needs in embedded systems and data processing

---
Maintained by bartekM
Last updated: April 2025
