#SSAT Anotation Tool
SSAT is presentely an in-progress project of a free and interactive anotation tool for the computer vision community, it eases
the way reseachers can annotate data from massive video datasets.
##Instalation
Note that for the moment the annotation tool has only versions for MAC and Windows, to install the tool in this two operating systems
visit this link and dowload the application installer <insert link here>
##Proper use
There are a few requirements thata make the SSAT work properly.
  * No operation can be executed if no videos has been previously loaded, to load a video press "File" in the menu bar and then "Open"
  (or use the sortcut CTR + O)an open dialog will pop up and you can select any video that has a format .mp4 or .avi
  ![Alt text](/images/image1.png?raw=true "SSAT screen with no loaded video")
  Note that in the image all features are locked because no video has been loaded
  ![Alt text](/images/image2.png?raw=true "SSAT screen with a loaded video")
  After the video is loaded, all functionalities start to work properly
  
  * Before begining the annotation the user must establish the atributes in wich he desire to base his annotations , to do this select
  "Annotation" in the menu bar followed by attributes, another dialog will pop up and the user can create an hierarchy of 
  categorys(filters) and labels.
  ![Alt text](/images/image3.png?raw=true "Attributes screen")
  The attributes box, showed in the image above, will be initialy empty, the attributes are defined following an hierarchy of categorys and labels, this hierarchy was created to ease to use of the tool in the midst of a high number of different labels.
  Hence  a category can be understood as an collection of labels, that have something in common. It is not possible to create a label that doesn´t belong to a category, so the "insert label" button remains deativated until an category is selected, the user can also edit an annotation already made by double clicking it on the table and making the desired changes.
  * There are two tipes of annotation frame based annotation and bounding-box based, the former comprises the whole video frame
  whereas the latter specifies a region(box) from the video picture, to annotate right-click on the video and then choose between frame based and bounding box based..
    1. Frame boxes hold the following info: category, label, initial frame, final frame and general information.  
    2. Bounding boxes encompass information like: category, label, initial frame, final frame, x-axis position, y-axis position,width, height, and general information.
   
   
   Presently, the bounding box based annotations are still being developed hence, they do not work properly,  the user can create boxes on the screen and they are saved, but the bounding boxes can't be removed or changed in the core of the SSAT
      
   * Whenever the user decides to import/export a file he must click on file and then selects import/export JSON and then specify
   either desired the file to import or the folder to export. Note that every 10 seconds a security file will be exported for the root
   directory and if the user open a video he already has opened before, he will be asked to import this security copy.
