# **3DViewer_v2.0**

![prev](misc/3d3.jpg)

## **Information**

3DViewer_v2.0 is a C++ application for viewing 3D wireframe models in the object-oriented programming paradigm, implementing the same features as the previously developed application in the [3DViewer v1.0](https://github.com/Hasuk1/School-21-3DViewer_v1.0) project.

![gif](misc/gif.gif)

## **Project Architecture**
The project is implemented within the MVC pattern, where other design patterns are also applied.

![diagram](misc/diagram.jpeg)

## **What this app can do**

![screen](misc/screen.png)

1. Selecting model file and displaying its name: The user can select the model file through the dialog box and the name of the selected file will be displayed in the corresponding field on the interface.

2. Visualization of the wireframe model: The visualization area allows you to display the loaded model as a wireframe model representing vertices and edges.

3. Model translation: The user can specify parameters for model translation along X, Y and Z axes using the corresponding input fields and buttons.

4. Model rotation: The user can set the rotation angle for the model around the X, Y and Z axes using the input fields and buttons.

5. Model scaling: The user can change the scale of the model using the input field and buttons.

6. Information about the loaded model: The information section displays the name of the loaded file, the number of vertices and edges in the model.

7. User settings:
 - Projection type. User can select the projection type to display the model parallel or center.

 - Rib and vertex display settings. User can configure the type (solid, dashed), color and thickness of the edges, and the vertex display method (none, circle, square), color and size.

 - Background color selection: The user can select the background color for the visualization area.
 
    User settings are saved, so that they will be restored the next time the application is launched.

8. Creating a screenshot: The user can click the "screenshot" button to save the current view of the model as a screenshot image.

9. Creating a gif animation (gif): The user can click the "gif" button to record a screencast of the current user affine transformations of the model into gif animation format. The animation will have a resolution of 640x480, a speed of 10 frames per second and a duration of 5 seconds.

## **Supported platforms**

- [x] Linux
- [x] MacOS
- [ ] Windows

## **Stack**

<div>
    <img src="https://github.com/devicons/devicon/blob/master/icons/cplusplus/cplusplus-original.svg" title="CPLUS" alt="CPLUS" width="40" height="40"/>&nbsp;
    <img src="misc/2560px-Qt_logo_2016.svg.png" title="CPLUS" alt="CPLUS" width="40" height="30"/>&nbsp;
    <img src="https://github.com/devicons/devicon/blob/master/icons/c/c-original.svg" title="C" alt="C" width="40" height="40"/>&nbsp;
    <img src="https://github.com/devicons/devicon/blob/master/icons/docker/docker-original.svg" title="docker" alt="docker" width="40" height="40"/>
</div>

## **Installation**

```shell
git clone git@github.com:Hasuk1/School-21-3DViewer_v2.0.git
cd School-21-3DViewer_v2.0/src
make install
```