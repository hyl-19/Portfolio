# Real-Time Sounds Detector Embedded on Raspberry Pi

A lightweight, low-power real-time sound classification system combining LAION-AI’s CLAP model with a Raspberry Pi. It captures, processes, and classifies environmental sounds on-device, displaying live annotations and generating summary reports with frequency and duration analyses. 

---

## Features

- **Live audio capture & preprocessing**  
  - WAV conversion (float32 → int16), queue buffering  
  - Dynamic window-and-stride segmentation

- **Contrastive audio–text embedding**  
  - HTSAT-based audio encoder (time, frequency, semantic features)  
  - RoBERTa text encoder with keyword-to-caption augmentation  
  - MLP projection + cosine-based contrastive learning  

- **Real-time classification UI**  
  - Live timestamped annotations of detected sound classes  
  - “Generate Results” button for report creation  

- **Summary analytics & visualization**  
  - Top-frequency sound types (pie chart, bar chart)  
  - Longest-duration continuous sounds  
  - HTML/PNG report export  

---

## Results & Analysis

- **Accuracy on PC vs. Raspberry Pi**
  - PC: 77.8 %
  - Raspberry Pi 4: 60.3 %

- **Fixed Window vs. Window-Stride**
  - Fixed window (4 s): 77.8 %
  - Window-stride (4 s window, 3 s stride): 83.4 %

- **Performance**
  - PC processing time: ~0.5 s/audio clip
  - Raspberry Pi processing time: ~1.8 s/audio clip

- **Future Work**
  - Data augmentation & balancing to improve rare-class accuracy
  - On-device noise reduction (adaptive filters, deep denoising)
  - Array-mic support for beamforming & noise suppression

## Datasets & Models

UrbanSound8K, ESC-50, FSD50K
LAION-AI CLAP: Contrastive Language-Audio Pretraining



