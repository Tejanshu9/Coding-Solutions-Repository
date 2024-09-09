<pre>
WWDC                                <a href="https://gist.github.com/IsaacXen/874c59aec92a13f30728aecdabb9ea80#file-wwdc2006">2006</a>  <a href="https://gist.github.com/IsaacXen/874c59aec92a13f30728aecdabb9ea80#file-wwdc2007">2007</a>  <a href="https://gist.github.com/IsaacXen/874c59aec92a13f30728aecdabb9ea80#file-wwdc2008">2008</a>  <a href="https://gist.github.com/IsaacXen/874c59aec92a13f30728aecdabb9ea80#file-wwdc2009">2009</a>
<a href="https://gist.github.com/IsaacXen/874c59aec92a13f30728aecdabb9ea80#file-wwdc2010">2010</a>  <a href="https://gist.github.com/IsaacXen/874c59aec92a13f30728aecdabb9ea80#file-wwdc2011">2011</a>  <a href="https://gist.github.com/IsaacXen/874c59aec92a13f30728aecdabb9ea80#file-wwdc2012">2012</a>  <a href="https://gist.github.com/IsaacXen/874c59aec92a13f30728aecdabb9ea80#file-wwdc2013">2013</a>  <a href="https://gist.github.com/IsaacXen/874c59aec92a13f30728aecdabb9ea80#file-wwdc2014">2014</a>  <a href="https://gist.github.com/IsaacXen/874c59aec92a13f30728aecdabb9ea80#file-wwdc2015">2015</a>  <a href="https://gist.github.com/IsaacXen/874c59aec92a13f30728aecdabb9ea80#file-wwdc2016">2016</a>  <a href="https://gist.github.com/IsaacXen/874c59aec92a13f30728aecdabb9ea80#file-wwdc2017">2017</a>  <a href="https://gist.github.com/IsaacXen/874c59aec92a13f30728aecdabb9ea80#file-wwdc2018">2018</a>  <a href="https://gist.github.com/IsaacXen/874c59aec92a13f30728aecdabb9ea80#file-wwdc2019">2019</a>
<a href="https://gist.github.com/IsaacXen/874c59aec92a13f30728aecdabb9ea80#file-wwdc2020">2020</a>  <a href="https://gist.github.com/IsaacXen/874c59aec92a13f30728aecdabb9ea80#file-wwdc2021">2021</a>  <a href="https://gist.github.com/IsaacXen/874c59aec92a13f30728aecdabb9ea80#file-wwdc2022">2022</a>  <a href="https://gist.github.com/IsaacXen/874c59aec92a13f30728aecdabb9ea80#file-wwdc2023">2023</a>  <a href="https://gist.github.com/IsaacXen/874c59aec92a13f30728aecdabb9ea80#file-wwdc2024">2024</a>
<a href="https://gist.github.com/IsaacXen/874c59aec92a13f30728aecdabb9ea80#file-techtalks">Tech Talks</a>        <a href="https://gist.github.com/IsaacXen/874c59aec92a13f30728aecdabb9ea80#file-app-store-connect">App Store Connect</a>       <a href="https://gist.github.com/IsaacXen/874c59aec92a13f30728aecdabb9ea80#file-insights">Insights</a>
</pre>

## Usage

```shell
aria2c --input-file=<#file#>
```

## FAQ

<details>
<summary>Q: HTTP error 403 while downloading 2007～2012 videos?</summary>

You need a special cookies to download videos from 2007 ~ 2012.
Some videos requires cookies with your AppleID signed in (previously on `developer.apple.com/devcenter`). Here's how:

1. Open any video links during 2007 ~ 2012, but with `http://developer.apple.com/services-account/download?path=` prefix. for example, [this one](http://developer.apple.com/services-account/download?path=/ios/ios_5_tech_talk_world_tou/adopting_icloud_storage__part_1.mov).

   This will add `ADCDownloadAuth` to your cookies.
   
2. Open your browser's developer tools and navigate to the cookies section:

   **Safari**
   
   1. Enable ***Safari -> Settings -> Advanced -> Show Develop menu in menu bar***
   2. Open web inspector with ***Develop -> Open Web Inspector*** (or `Option + Command + I`)
   3. Head to ***Storage*** tab, and select ***Cookies*** on side bar
   
   **Chrome**
   
   1. Open Developer Tools with ***View -> Developer -> Developer Tools*** (or `Option + Command + I` on Mac, `F12` on Windows)
   2. Head to ***Application*** tab, then ***Cookies*** on side bar, select the url item within it.
   
3. Locale `ADCDownloadAuth` and copy the value to the clipboard.

4. Create a `cookies.txt` file with following content:

   ```
   # Netscape HTTP Cookie File
   .apple.com	TRUE	/	TRUE	0	ADCDownloadAuth	<#Value#>
   ```
   
   Replace the `<#Value#>` with your value copied from last step. Notice that each fields in this file are separated with a tab (`\t`).
   
   > [!NOTE]
   > We are using `0` here in the `expire` field because it doesn't metter when downloading. Do note that once the cookies expired, you will need to obtain a new token by login to `/services-account` again.
   >
   > For more details on the Netscape's cookies file format, see [this](http://curl.haxx.se/rfc/cookie_spec.html) and [this](http://fileformats.archiveteam.org/wiki/Netscape_cookies.txt).

5. Load cookies to aria2 with `--load-cookies` option:
 
   ```bash
   aria2c --load-cookies=/path/to/cookies.txt --input-file=<#file#>
   ```

</details>

<details>
<summary>Q: I can't download any video from 2013 with aria2.</summary>

For some reasons 2013 videos can't be download directly, but there's a workaround: we can download the stream as video.

Take session 201 as an example, here's the HD url to the sesson video:

```
https://devstreaming-cdn.apple.com/videos/wwdc/2013/201xex2xxf5ynwnsgl/201/201-HD.mov
```

Change it to the stream file version. The file name can be found from source in `developer.apple.com/videos/play/wwdc2013/201` (use wayback machine, search `m3u8`):

```
https://devstreaming-cdn.apple.com/videos/wwdc/2013/201xex2xxf5ynwnsgl/201/ipad_c.m3u8
```

Now we can use `youtube-dl` to extract and download it. First install `youtube-dl`:

```bash
brew install youtube-dl
```

Then, use `youtube-dl` to download the video with best quality:

```bash
youtube-dl -f best --output "[2013] [Session 201] Building User Interfaces for iOS 7.mp4" https://devstreaming-cdn.apple.com/videos/wwdc/2013/201xex2xxf5ynwnsgl/201/ipad_c.m3u8
```

For batch download, use `wwdc2013-hls.sh`, remember to `chmod +x wwdc2013-hls.sh`.

Down side is that there's no parallel downloading :(.

> The `-f best` choose the stream with best quality automatically, but won't always works. If you encounter `requested format not available` error with `-f best` option, you may pick a format manually, here's how:
> 
> First, use `--list-formats` to list all streams available:
> 
> ```bash
> youtube-dl --list-formats <URL>
> # [generic] cmaf: Requesting header
> # [generic] cmaf: Downloading m3u8 information
> # [info] Available formats for cmaf:
> # format code                   extension  resolution note
> #
> # (more formats here...)
> #
> # 799                           mp4        1920x1080   799k , hvc1.1.6.H120.B0, 29.97fps, video only
> # 1044                          mp4        2560x1440  1044k , hvc1.1.6.H150.B0, 29.97fps, video only
> # 2277                          mp4        3840x2160  2277k , hvc1.1.6.H150.B0, 29.97fps, video only (best)
> ```
> 
> Pick a format you want to download, for example, we are downloading `2277` because it has the best quality. Use `-f` option to choose the format:
>
> ```bash
> youtube-dl -f 2277 <URL> --output <FILENAME>
> ```
>
> Some stream split video and audio into different tracks (as shown above, `video only` suggests that this format contains only video track). In this case, use `-f VIDEO_FORMAT+AUDIO_FORMAT` instead to download both video and audio tracks. For example `-f bestvideo+bestaudio`, `-f 2277+bestaudio`.

> This technique should also works for video that's broken / fail to download / no download link provided, as long as it has the m3u8 file.

</details>

<details>
<summary>Q: Why I can only download some Tech Talks 2013 videos?</summary>

Short anwser is: I don't know. However, I can tell you how I found these links for "some video".

The original download URL can be found [here](https://web.archive.org/web/20150315005313/https://developer.apple.com/tech-talks/videos/). for example, this is the HD URL for tech talks 22:

```
http://devstreaming.apple.com/videos/techtalks/2013/22_Advances_in_OpenGL_ES_3_0/Advances_in_OpenGL_ES_3_0-hd.mov
```

This domain has been replaced with `devstreaming-cdn.apple.com`. so by changing the domain, we can still download some of them, namly:

```
Advances in OpenGL ES 3.0
App Store Distribution and Marketing for Games
Architecting Modern iOS Games
Developing 2D Games with Sprite Kit
Game Developer Day Kickoff
Hidden iOS 7 Development Gems
Integrating iOS 7 Game Technologies
Integrating iOS 7 System Technologies
User Interface Design for iOS 7 Games
```

> I mean "some", because the following videos just won't works:
> 
> ```
> App Developer Day Kickoff
> User Interface Design for iOS 7 Apps
> Architecting Modern Apps, Part 1
> App Store Distribution and Marketing for Apps
> Architecting Modern Apps, Part 2
> Integrating iOS 7 Technologies
> Security and Privacy in iOS 7
> ```

If you encounter a "can't play" error (in safari, this is a play icon with a slash), a simple fix is to refresh (or retry in aria2).

An alternative way to downlaod these is to download the video fragments with `m3u8` file. Open [this page](https://web.archive.org/web/20150315005313/https://developer.apple.com/tech-talks/videos/) in the browser, click any title and then play button, you will see a player show up and a spinning indicator. Open your developer tool and select the player element, you will see that the video url points to `ref.mov`:

```
http://devstreaming-cdn.apple.com/videos/techtalks/2013/22_Advances_in_OpenGL_ES_3_0/ref.mov
```

Open this URL in a new tab, and check the developer tool's network tab, you can see it's accessing the `sl.m3u8` file. 

```
http://devstreaming-cdn.apple.com/videos/techtalks/2013/22_Advances_in_OpenGL_ES_3_0/sl.m3u8
```

With this URL, we can now download it with youtube-dl, as the previous Q&A had shown.

</details>

<details>
<summary>Q: Some link no longer works.</summary>

There's not much I can do about it.

Apple is known for breaking links to old session videos. Sometime we are lucky to find new working links, but most of the time don't.

If you value these session videos, download a copy beforehand when it's possible, just in case.

</details>

<details>
<summary>Q: Can you share your archives?</summary>

If only there's a realiable way to share it.

I used to share the entire archives on OneDrive and GDrive, both account got banned for abuse after some time.

Edit: @krackers points out that we can upload to internet archive. I poked around and found that (A) some one else already upload some videos to it. (B) There are 500GB limit pre item, which is more than enough if we group these videos yearly. (C) It allow adding new files to it in the future. I'll try to upload some of the videos when I'm free, we'll see how it goes.

</details>

## Note

<details><summary>WWDC 2005</summary>

- For <strong>Session 138: AppleScript for Programers: Essential Tools and Tips</strong>, macosxautomation.com has a copy of the video hosted <a href="https://macosxautomation.com/applescript/wwdc-session-138.html">here</a>.

</details>

<details><summary>WWDC 2008</summary>
<pre>
[CORRUPTED]
Session 453: <a href="https://download.developer.apple.com/wwdc_2008/adc_on_itunes__wwdc08_sessions__mac_track__videos/453.m4v">Using Vectorization Techniques to Maximize Performance</a>
Session 520: <a href="https://download.developer.apple.com/wwdc_2008/adc_on_itunes__wwdc08_sessions__it_track__videos_2/520.m4v">Deploying and Scaling iCal Server Calendaring Services</a>
Session 557: <a href="https://download.developer.apple.com/wwdc_2008/adc_on_itunes__wwdc08_sessions__it_track__videos_2/557.m4v">Infrastructure and Deployment Techniques for Large-Scale On-Demand Content Delivery with the Mac</a>
&nbsp;
[MISSING]
Session 105: Publishing on the App Store
Session 312: iPhone Application Development Fundamentals
Session 313: Getting Started with Web Development for Safari on iPhone
Session 324: iPhone for Mac Developers
Session 337: Understanding iPhone View Controllers
Session 343: Understanding iPhone Table Views
Session 351: iPhone Application User Interface Design
Session 352: Web Development for iPhone: Tips, Tricks, and Advanced Techniques
Session 362: Controls, Views, and Animation on iPhone
Session 379: Enhancing Your iPhone Web Application with CSS Transforms and Animations
Session 380: iPhone Multi-Touch Events and Gestures
Session 387: Text Input on iPhone
Session 391: Building an Advanced iPhone Web Application, Hands On
Session 402: Managing Secure Data on iPhone
Session 410: Mastering iPhone View Controllers
Session 417: Optimizing Performance in iPhone Applications
Session 432: Mastering iPhone Table Views
Session 446: How Do I Do That? Tips and Tricks for iPhone Application Development
Session 456: The KPCB iFund
Session 520: Deploying and Scaling iCal Server Calendaring Services
Session 529: Address Book for iPhone
Session 546: iPhone Device APIs: Location, Accelerometer and Camera
Session 703: Introduction to Game Development for iPhone
Session 706: Audio Development for iPhone
Session 708: 3D Graphics for iPhone using OpenGL ES 
Session 901: Introduction to the iPhone Development Tools
Session 921: Using Dashcode to Create and Debug iPhone Web Applications
Session 925: Debugging and Profiling Your iPhone Application
</pre>

As suggested by [@ZhongWentao2002](#gistcomment-4689103), some session videos seems to have a copy on apple server. Take session 916 as an example, url (1) points to a 28 seconds corrupted video, but url (2) points to a full 53m23s video:
   
```
# (1)
https://download.developer.apple.com/wwdc_2008/adc_on_itunes__wwdc08_sessions__mac_track__videos_2/916.m4v

# (2)
https://download.developer.apple.com/wwdc_2008/adc_on_itunes__wwdc08_sessions__mac_track__videos/916.m4v
```

This seem to only apply to `mac_track` videos, no `it_track` and `iphone_track`.

Session 453, sadly, is corrupted for both url.
</details>

<details><summary>WWDC 2009</summary>
<pre>
[CORRUPTED] (right link, broken file)
Session 101: <a href="https://download.developer.apple.com/wwdc_2009/adc_on_itunes__wwdc09_sessions__iphone_track__video/101__perfecting_your_iphone_table_views.m4v">Perfecting Your iPhone Table Views</a>
Session 105: <a href="https://download.developer.apple.com/wwdc_2009/adc_on_itunes__wwdc09_sessions__iphone_track__video/105__cut_copy_and_paste_on_iphone.m4v">Cut, Copy, and Paste on iPhone</a>
Session 111: <a href="https://download.developer.apple.com/wwdc_2009/adc_on_itunes__wwdc09_sessions__mac_track__video/111__nsimage_in_snow_leopard.m4v">NSImage in Snow Leopard</a>
Session 200: <a href="https://download.developer.apple.com/wwdc_2009/adc_on_itunes__wwdc09_sessions__mac_track__video/200__leveraging_web_content_in_mac_os_x_applications_with_webkit.m4v">Leveraging Web Content in Mac OS X Applications with WebKit</a>
Session 208: <a href="https://download.developer.apple.com/Safari/adc_on_itunes__sdc/session_208__creating_safari_web_applications_in_dashcode.m4v">Creating Safari Web Applications in Dashcode</a>
Session 320: <a href="https://download.developer.apple.com/wwdc_2009/adc_on_itunes__wwdc09_sessions__mac_track__video/320__image_processing_and_effects_with_core_image.m4v">Image Processing and Effects with Core Image</a>
Session 404: <a href="https://download.developer.apple.com/wwdc_2009/adc_on_itunes__wwdc09_sessions__mac_track__video/404__using_automator_and_services_to_integrate_with_mac_os_x.m4v">Using Automator and Services to Integrate with Mac OS X</a>
Session 420: <a href="https://download.developer.apple.com/wwdc_2009/adc_on_itunes__wwdc09_sessions__iphone_track__video/420__introduction_to_objectivec.m4v">Introduction to Objective-C</a>
&nbsp;
[MISSING] (wrong link)
Session 130: <a href="https://download.developer.apple.com/wwdc_2009/adc_on_itunes__wwdc09_sessions__mac_track__video/130__performance_tuning_with_shark_and_intels_processor_performance_events.m4v">Performance Tuning with Shark and Intel's Processor Performance Events</a>
Session 500: <a href="https://download.developer.apple.com/wwdc_2009/adc_on_itunes__wwdc09_sessions__mac_track__video/500__managing_processes_with_launchd.m4v">Managing Processes with launchd</a>
Session 604: <a href="https://download.developer.apple.com/wwdc_2009/adc_on_itunes__wwdc09_sessions__mac_track__video/604__managing_home_directories_with_mac_os_x_server.m4v">Managing Home Directories with Mac OS X Server</a>
&nbsp;
<a href="https://web.archive.org/web/20091229075410/http://devimages.apple.com/products/video/wwdc09/wwdc09sessionlist.pdf">Session List</a>
</pre>
</details>

<details><summary>WWDC 2011</summary>
<pre>
[URL PATTERN]
HD:     https://download.developer.apple.com/videos/wwdc_2011__hd/session_<#SESSION_ID#>__<#SNAKECASE_TITLE#>.m4v
SD:     https://download.developer.apple.com/videos/wwdc_2011__sd/session_<#SESSION_ID#>__<#SNAKECASE_TITLE#>.m4v
STREAM: https://devstreaming-cdn.apple.com/videos/wwdc/2011/<#SESSION_ID#>/ipad_c.m3u8
PDF:    https://download.developer.apple.com/wwdc_2011/adc_on_itunes__wwdc11_sessions__pdf/<#SESSION_ID#>_<#SNAKECASE_TITLE#>.pdf
</pre>
</details>


<details><summary>WWDC 2012</summary>
<pre>
[URL PATTERN]
HD:     https://download.developer.apple.com/videos/wwdc_2012__hd/session_<#SESSION_ID#>__<#SNAKECASE_TITLE#>.mov
SD:     https://download.developer.apple.com/videos/wwdc_2012__sd/session_<#SESSION_ID#>__<#SNAKECASE_TITLE#>.mov
STREAM: https://devstreaming-cdn.apple.com/videos/wwdc/ljbofiuvboiubvoiubseoriubvbip/<#SESSION_ID#>/ipad_c.m3u8
PDF:    https://download.developer.apple.com/wwdc_2012/wwdc_2012_session_pdfs/session_<#SESSION_ID#>__<#SNAKECASE_TITLE#>.pdf
</pre>
</details>

<details><summary>WWDC 2013</summary>
<pre>
[URL PATTERN]
HD:     https://devstreaming-cdn.apple.com/videos/wwdc/2013/<#ID#>/<#SESSION_ID#>/<#SESSION_ID#>-HD.mov
SD:     https://devstreaming-cdn.apple.com/videos/wwdc/2013/<#ID#>/<#SESSION_ID#>/<#SESSION_ID#>-SD.mov
STREAM: https://devstreaming-cdn.apple.com/videos/wwdc/2013/<#ID#>/<#SESSION_ID#>/ipad_c.m3u8
PDF:    https://devstreaming-cdn.apple.com/videos/wwdc/2013/<#ID#>/<#SESSION_ID#>/<#SESSION_ID#>.pdf
SUBS:   https://devstreaming-cdn.apple.com/videos/wwdc/2013/<#ID#>/<#SESSION_ID#>/subtitles/eng/prog_index.m3u8
</pre>
</details>

<details><summary>WWDC 2014</summary>
<pre>
[URL PATTERN]
HD:     https://devstreaming-cdn.apple.com/videos/wwdc/2014/<#ID#>/<#SESSION_ID#>/<#SESSION_ID#>_hd_<#SNAKECASE_TITLE#>.mov
SD:     https://devstreaming-cdn.apple.com/videos/wwdc/2014/<#ID#>/<#SESSION_ID#>/<#SESSION_ID#>_sd_<#SNAKECASE_TITLE#>.mov
STREAM: https://devstreaming-cdn.apple.com/videos/wwdc/2014/<#ID#>/<#SESSION_ID#>/ref.mov
PDF:    https://devstreaming-cdn.apple.com/videos/wwdc/2014/<#ID#>/<#SESSION_ID#>/<#SESSION_ID#>_<#SNAKECASE_TITLE#>.pdf
SUBS:   https://devstreaming-cdn.apple.com/videos/wwdc/2014/<#ID#>/<#SESSION_ID#>/subtitles/eng/prog_index.m3u8
</pre>
</details>

<details><summary>WWDC 2017</summary>
<pre>
[HLS ONLY]
Session 101: <a href="https://events-delivery.apple.com/17qopibbefvoiuhbsefvbsefvopihb06/m3u8/hls_vod_mvp.m3u8">Keynote</a>
Session 102: <a href="https://devstreaming-cdn.apple.com/videos/wwdc/2017/102xyar2647hak3e/102/hls_vod_mvp.m3u8">Platforms State of the Union</a>
</pre>
</details>

<details><summary>WWDC 2018</summary>
<pre>
[HLS ONLY]
Session 101: <a href="https://events-delivery.apple.com/18oijbasfvuhbfsdvoijhbsdfvljkb6/m3u8/hls_vod_mvp.m3u8">Keynote</a>
Session 102: <a href="https://devstreaming-cdn.apple.com/videos/wwdc/2018/102ly3xmvz1ssb1ill/102/hls_vod_mvp.m3u8">Platforms State of the Union</a>
Session 715: <a href="https://devstreaming-cdn.apple.com/videos/wwdc/2018/715o2fzpdzzzf5f0/715/hls_vod_mvp.m3u8">Introducing Network.framework: A modern alternative to Sockets</a>
Session 803: <a href="https://devstreaming-cdn.apple.com/videos/wwdc/2018/803lpnlacvg2jsndx/803/hls_vod_mvp.m3u8">Designing Fluid Interfaces</a>
Session 805: <a href="https://devstreaming-cdn.apple.com/videos/wwdc/2018/805llmiw0zwkox4zhuc/805/hls_vod_mvp.m3u8">Creating Great AR Experiences</a>
</pre>
</details>


<details><summary>WWDC 2019</summary>
<pre>
[HLS ONLY]
Session 101: <a href="https://events-delivery.apple.com/3004qzusahnbjppuwydgjzsdyzsippar/m3u8/hls_vod_mvp.m3u8">Keynote</a>
Session 103: <a href="https://devstreaming-cdn.apple.com/videos/wwdc/2019/103bax22h2udxu0n/103/hls_vod_mvp.m3u8">Platforms State of the Union</a>
Session 104: <a href="https://devstreaming-cdn.apple.com/videos/wwdc/2019/104d6zyhb21vki/104/hls_vod_mvp.m3u8">Apple Design Awards</a>
</pre>
</details>

<details><summary>WWDC 2024</summary>
<pre>
[HLS ONLY]
Session 101: <a href="https://events-delivery.apple.com/1505clvgxdwlbjrjhxtjdgcdxaiabvuf/m3u8/vod_index-LHDoZDhTrsKLsbrZKqYpbWraixsWQHkw.m3u8">Keynote</a>
Session 111: <a href="https://events-delivery.apple.com/1505clvgxdwlbjrjhxtjdgcdxaiabvuf/m3u8/vod_asl_index-jTZXsamshpmJjncxPxevscCcyQyaWkkU.m3u8">Keynote (ASL)</a>
</pre>
</details>

> <details><summary>These sessions can be downloaded, but the file is currupted:</summary>
> <pre>
> WWDC 2013 Session 710: A Practical Guide to the App Sandbox
> WWDC 2013 Session 712: Energy Best Practices
> </pre>
> </details>

> <details><summary>These sessions are downloaded in SD because HD is broken:</summary>
> <pre>
> WWDC 2011 Session 310: What's New in Instruments
> WWDC 2011 Session 311: Masterinng Source Control in XCode
> WWDC 2011 Session 320: Adopting Multitasking in Your App
> WWDC 2012 Session 222: Introduction to Attributed Strings for iOS
> WWDC 2012 Session 227: Using iCloud with Core Data
> WWDC 2012 Session 305: What's New in iTunes Connect for App Developers
> WWDC 2012 Session 406: Adopting Automatic Reference Counting
> WWDC 2012 Session 501: Publishing with the iBookStore
> WWDC 2012 Session 703: Core Bluetooth 101
> WWDC 2012 Session 708: The Accelerate Framework
> </pre>
> </details>

> <details><summary>These sessions can be stream online, but has no download link provided:</summary>
> <pre>
> WWDC 2019 Session    101: <a href="https://developer.apple.com/videos/play/wwdc2019/101">Keynote</a>
> WWDC 2019 TechTalk   609: <a href="https://developer.apple.com/videos/play/tech-talks/609">Advanced Scene Understanding in AR</a>
> WWDC 2019 TechTalk   610: <a href="https://developer.apple.com/videos/play/tech-talks/610">Get to know Reality Composer</a>
> WWDC 2020 Session    101: <a href="https://developer.apple.com/videos/play/wwdc2020/101">Keynote</a>
> WWDC 2020 Session  20022: <a href="https://developer.apple.com/videos/play/wwdc2020/20022">Apple Design Awards</a>
> WWDC 2020 TechTalk 10865: <a href="https://developer.apple.com/videos/play/tech-talks/10865">What can you do on an Apple silicon Mac?</a>
> WWDC 2021 Session    101: <a href="https://developer.apple.com/videos/play/wwdc2021/101">Keynote</a>
> WWDC 2021 Session    111: <a href="https://developer.apple.com/videos/play/wwdc2021/111">Keynote (ASL)</a>
> WWDC 2022 Session    101: <a href="https://developer.apple.com/videos/play/wwdc2022/101">Keynote</a>
> WWDC 2022 Session    111: <a href="https://developer.apple.com/videos/play/wwdc2022/111">Keynote (ASL)</a>
> WWDC 2022 Session  10113: <a href="https://developer.apple.com/videos/play/wwdc2021/10113">Explore EDR on iOS</a>
> WWDC 2022 Session  10114: <a href="https://developer.apple.com/videos/play/wwdc2021/10114">Display EDR content with Core Image, Metal, and SwiftUI</a>
> Developer Insights   112: <a href="https://developer.apple.com/videos/play/insights/112">Using Subscriptions</a>
> </pre>
>
> Use the **hls-only** script to download the stream.
>
> </details>

> <details><summary>These sessions are presented during WWDC but was split into multiple videos:</summary>
> <pre>
> WWDC 2019 Session 201: Accessibility Lessons
>        -> Session 244: Visual Design and Accessibility
>        -> Session 250: Making Apps More Accessible With Custom Actions
>        -> Session 254: Writing Great Accessibility Labels
>        -> Session 257: Accessibility Inspector
> WWDC 2019 Session 242: Getting the Most out of Multitasking
>        -> Session 258: Architecting Your App for Multiple Windows
>        -> Session 259: Targeting Content with Multiple Windows
> WWDC 2019 Session 504: What’s New in Authentication, Safari, and WebKit
>        -> Session 515: What's New in Safari
>        -> Session 516: What's New in Authentication
>        -> Session 518: What's New for Web Developers
> WWDC 2019 Session 711: Introducing Combine and Advances in Foundation
>        -> Session 722: Introducing Combine 
>        -> Session 723: Advances in Foundation
> WWDC 2019 Session 801: What's New in iOS and macOS Design
>        -> Session 808: What's New in iOS Design
>        -> Session 809: Designing iPad Apps for Mac
> WWDC 2019 Session 804: Designing and Building Great Shortcuts
>        -> Session 805: Building Great Shortcuts
>        -> Session 806: Designing Great Shortcuts
> </pre>
> </details>

> <details><summary>These sessions are no longer available:</summary>
> <pre>
> WWDC 2011 Session 600: <a href="https://developer.apple.com/videos/wwdc/2011/?id=600">Keynote</a>
> WWDC 2012 Session 100: <a href="https://developer.apple.com/videos/wwdc/2012/?id=100">Keynote</a>
> WWDC 2016 Session 717: <a href="https://developer.apple.com/videos/wwdc/2016/?id=717">Beyond Dictation — Enhanced Voice-Control for macOS Apps</a>
> WWDC 2019 Session 101: <a href="https://developer.apple.com/videos/wwdc/2019/?id=101">Keynote</a>
> </pre>
> </details>

## Archives

<pre>
[VIDEO]
                                          <a href="https://archive.org/details/10-opening-keynote">1997</a>        <a href="https://archive.org/details/apple-wwdc-99-presentations-cd">1999</a>
<a href="https://www.macintoshrepository.org/18729-apple-wwdc-2000-conference-sessions">2000</a>  <a href="https://archive.org/details/wwdc-2001-dvd-1-iso">2001</a>  <a href="https://archive.org/details/Wwdc2002DvdSet">2002</a>  <a href="https://archive.org/details/Apple_WWDC_2003_DVDs">2003</a>  <a href="https://www.macintoshrepository.org/26106-apple-wwdc-2004-conference-sessions">2004</a>              <a href="https://archive.org/details/2007-session-616-designing-and-developing-hybrid-web-or-cocoa-applications">2007</a>  <a href="https://archive.org/details/2008-session-725-application-printing-in-mac-os-x">2008</a>  <a href="https://archive.org/details/wwdc-2009-sessions">2009</a>
            <a href="https://archive.org/details/wwdc-2012-sessions">2012</a>        <a href="https://archive.org/details/wwdc-2014-videos-sessions">2014</a>  <a href="https://archive.org/details/wwdc2015videos">2015</a>  <a href="https://archive.org/details/wwdc2016videos">2016</a>
<a href="https://archive.org/details/wwdc2020videos">2020</a>

[TRANSCRIPT]
<a href="https://github.com/ASCIIwwdc/wwdc-session-transcripts/tree/master">ASCIIWWDC</a>

[PDF]
<a href="https://docs.huihoo.com/apple/wwdc/">huihoo's archives for 2010-2020</a>

[Session List]
<a href="https://nonstrict.eu/wwdcindex/">WWDC Index</a>
</pre>

Note: Archives from Macintosh Repository requires paid account to download.

## Changelog

**June 14, 2024**

- 2024: Add `wwdc2024` & `wwdc2024-hls.sh`.

**June 7, 2024**

- 2019: Add `wwdc2019-hls.sh`.

**June 5, 2024**

- 2006: Add link to 000 and 101. (See [this comment](#gistcomment-5079503))
- 2005: Add link to 138. (See **Note -> WWDC 2005**) The video is hosted by thrid-party (non-apple), so I'm not adding it as a file.
- Tech talks: Add 111374, 111376, 111373, 111372, 111384, 111377, 111378, 111369, 111381, 111386.

<details><summary>See More</summary>

**December 21, 2023**

- 2019: Add link to 619. (See [this comment](#gistcomment-4802826))

**October 17, 2023**

- README: Add url patterns info for 2011 ~ 2014.

**September 25, 2023**

- 2018: Add `wwdc2018-hls.sh` for stream-only 101, 102, 715, 803, 805.

**September 17, 2023**

- 2017: Add link to 814, and `wwdc2017-hls.sh` for stream-only 101, 102.
   
**September 12, 2023**

- 2008: Fix typo on session 936.

**September 12, 2023**

- 2008: Update links to 339, 426, 911, 916, you can now downlaod the full video.
- README: Add note for 2008.
   
**September 4, 2023**
  
- 2009: Add links to session 200, 501, 610.
- Update README
  - Add enternal link to 1997.
  - Add enternal link to PDFs archive (2010~2020).
  - Add note for 2009.
  - Cleaning up (still WIP).
   
**August 8, 2023**
  
- Update links and fix typos, see [@tomlokhorst's comment](#gistcomment-4654228)

**July 20, 2023**

- New download links has been found for 2007 ~ 2012.
- 2013 is still not available.
- 2014+ is working as usual.

**Jun 17, 2023**

- Add links to 2023.

**Mar 18, 2023**

- Add links to 2004, [spotted by cellularmitosis](#gistcomment-4507275).

**October 21, 2022**

- Add links to 2001 ~ 2003, Bundled in DVD set. The ISO image can be downloaded from Internet Archive.

**June 11, 2022**

- Add links for WWDC 2022.
  Four of them don't have download link provided:

  ```
    101: Keynote
    111: Keynote (ASL)
  10113: Explore EDR on iOS
  10114: Display EDR content with Core Image, Metal, and SwiftUI
  ```

**May 27, 2022**

- Add videos of Mac track and IT track from 2008, expect iPhone track:

  ```
  Session 105: Publishing on the App Store
  Session 312: iPhone Application Development Fundamentals
  Session 313: Getting Started with Web Development for Safari on iPhone
  Session 324: iPhone for Mac Developers
  Session 337: Understanding iPhone View Controllers
  Session 343: Understanding iPhone Table Views
  Session 351: iPhone Application User Interface Design
  Session 352: Web Development for iPhone: Tips, Tricks, and Advanced Techniques
  Session 362: Controls, Views, and Animation on iPhone
  Session 379: Enhancing Your iPhone Web Application with CSS Transforms and Animations
  Session 380: iPhone Multi-Touch Events and Gestures
  Session 387: Text Input on iPhone
  Session 391: Building an Advanced iPhone Web Application, Hands On
  Session 410: Mastering iPhone View Controllers
  Session 402: Managing Secure Data on iPhone
  Session 432: Mastering iPhone Table Views
  Session 417: Optimizing Performance in iPhone Applications
  Session 446: How Do I Do That? Tips and Tricks for iPhone Application Development
  Session 456: The KPCB iFund
  Session 529: Address Book for iPhone
  Session 546: iPhone Device APIs: Location, Accelerometer and Camera
  Session 703: Introduction to Game Development for iPhone
  Session 706: Audio Development for iPhone
  Session 708: 3D Graphics for iPhone using OpenGL ES
  Session 901: Introduction to the iPhone Development Tools
  Session 921: Using Dashcode to Create and Debug iPhone Web Applications
  Session 925: Debugging and Profiling Your iPhone Application
  ```
  
  The path is not `/wwdc_2008/adc_on_itunes__wwdc08_sessions__iphone_track__videos_2/`.

**May 26, 2022**

- Add most video links for WWDC 2009. Credit to @pvieito on [pointing out the method to assemble URLs](#gistcomment-4178962).

</details>