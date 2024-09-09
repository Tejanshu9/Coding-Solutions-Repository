#!/bin/bash
youtube-dl -f best --hls-prefer-native https://events-delivery.apple.com/17qopibbefvoiuhbsefvbsefvopihb06/m3u8/hls_vod_mvp.m3u8  --output "[2017] [Session 101] Keynote.mp4"
youtube-dl -f best --hls-prefer-native https://devstreaming-cdn.apple.com/videos/wwdc/2017/102xyar2647hak3e/102/hls_vod_mvp.m3u8 --output "[2017] [Session 102] Platforms State of the Union.mp4"