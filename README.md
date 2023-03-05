# Hazel-Engine

Hazel Engine is a simple Game Engine based on OpenGL and C++.

## 项目结构

### Hazel

- 引擎核心
- 编译后生成静态库文件
- 链接到Sandbox
- 由Sandbox调用

### HazelEditor

- 编辑器
- 构建应用程序或游戏

### Sandbox

- 测试项目
- 测试应用程序或游戏

## 开发过程

### 1. 项目入口点

- EntryPoint.h
- Application.h/.cpp
- SandBoxApp.cpp

### 2. 日志系统

- Log.h/.cpp

### 3. Premake构建项目

- premake.lua

### 4. 实现事件系统

- Event.h
- ApplicationEvent.h
- KeyEvent.h
- MouseEvent.h

### 5. 创建预编译头文件

- hzpch.h/.cpp

### 6. 窗口抽象和GLFW

- Window.h
- WindowsWindow.h/.cpp

### 7. 窗口事件

### 8. Layer

- Layer.h/.cpp
- LayerStack.h/.cpp

### 9. GLAD

### 10.ImGui层

- ImGuiLayer.h/.cpp

### 11. ImGui事件

### 12. 输入轮询

- Input.h
- WindowsInput.h/.cpp

### 13. 按键和鼠标代码

- KeyCodes.h
- MouseButtonKeyCodes.h

### 14. glm数学库

### 15. ImGui的docking

- ImGuiBuild.h

### 16. 静态库和零警告

### 17. 渲染上下文

### 18. 第一个三角形

- GraphicsContext.h
- OpenGLContext.h/.cpp

### 19. OpenGL着色器

- Shader.h/.cpp

### 20. 关于渲染器接口的抽象

- Buffer.h/.cpp
- OpenGLBuffer.h/.cpp
- Renderer.h/.cpp

### 21. 顶点缓冲区布局

### 22. 顶点数组

- VertexArray.h/.cpp
- OpenGLVertexArray.h/.cpp

### 23. 渲染流和渲染命令

- RenderCommand.h/.cpp
- RendererAPI.h/.cpp
- OpenGLRendererAPI.h/.cpp

### 24. 正交相机

- OrthographicCamera.h/.cpp

### 25. 移动渲染示例到SandBox

### 26. 帧间隔DeltaTime

- Timestep.h

### 27. Transforms

### 28. 着色器抽象

- OpenGLShader.h/.cpp

### 29. 纹理

- Texture.h/.cpp
- OpenGLTexture.h/.cpp

### 30. 颜色混合

### 31. 着色器资产文件

### 32. 着色器库

### 33. 正交相机控制器

- OrthographicCameraController.h/.cpp

### 34. 窗口缩放调整

### 35. 准备2D渲染

- Sandbox2D.h/.cpp

### 36. 开始2D渲染

- Renderer2D.h/.cpp

### 37. 2D渲染Transform

### 38. 2D渲染Texture

### 39. 基本性能测试

### 40.批渲染

### 41. 批渲染数据统计

### 42. 简单粒子系统

- ParticleSystem.h/.cpp

### 43. 创建子纹理

- SubTexture2D.h/.cpp

### 44. DockSpace

### 45. 帧缓冲区

- Framebuffer.h/.cpp
- OpenGLFramebuffer.h/.cpp

### 46. 场景视口

### 47. ImGuiLayer事件

### 48. 组件系统

- Scene.h/.cpp
- Components.h

### 49. 实体

- Entity.h/.cpp

### 50. 相机组件

- Camera.h
- SceneCamera.h/.cpp

### 51. 本地脚本

- ScriptableEntity.h

## 文件说明

### Hazel 项目

#### src

##### 预编译头文件

- hzpch.h/.cpp。

  包含引擎需要用到的C++标准库文件和其他库文件，预先编译为二进制文件，加快项目构建速度。

##### 外部文件

- spdlog

  外部日志库文件。

- GLFW

  外部窗口库文件，配合OpenGL。

##### Events

* Event.h

  定义所有事件基类 Event、事件调度器 EventDispatcher，定义事件类型 EventType 和事件种类 EventCategory。

* ApplicationEvent.h

  定义所有窗口事件、App事件。

* KeyEvent.h

  定义所有键盘事件 KeyEvent。

* MouseEvent.h

  定义所有鼠标事件。

##### Core

- Core.h

  引擎内核文件，定义引擎需要的宏和条件编译。

- Application.h/.cpp

  引擎应用程序入口，应用基类。定义所有事件处理函数，创建窗口并为窗口设置事件函数，接收事件并进行事件调度，将事件传递给层。创建ImGui层。定义引擎循环，更新层栈中的所有层，渲染GUI，更新窗口。

- EntryPoint.h

  引擎入口点，负责创建应用程序。

-  Log.h/.cpp

  引擎日志系统，定义内核日志和客户端日志基本格式。

- Hazel.h

  引用Hazel.dll需要包含的所有头文件。
  
- Window.h

  窗口类，所有窗口的抽象基类，可创建事件。

- Input.h

  输入类，定义按键鼠标输入接口。
  
- Timestep.h

  帧间隔，计算每帧之间的时间间隔。
  

##### Platforms

- WindowsWindow.h/.cpp

  Windows平台窗口，继承Window，创建GLFW窗口。
  
- WindowsInput.h.

  WInodws平台输入。
  
- OpenGLContext.h/.cpp

  OpenGL上下文类，继承GraphicsContext，初始化OpenGL上下文，交换双缓冲。

- OpenGLBuffer.h/.cpp

  OpenGL缓冲类，包含顶点缓冲和索引缓冲，分别继承VertexBuffer和IndexBuffer。
  
- OpenGLVertexArray.h/.cpp

  OpenGL顶点数组，链接多个顶点缓冲区和索引缓冲区，继承VertexArray。
  
- OpenGLRendererAPI.h/.cpp

  OpenGL渲染器接口，继承RendererAPI，执行最底层的OpenGL渲染指令。
  
- OpenGLShader.h/.cpp

  OpenGL着色器，继承Shader，执行OpenGL着色器指令。
  
- OpenGLTexture.h/.cpp

  OpenGL纹理，继承Texture，执行OpenGL纹理指令，加载和设置纹理。
  
- OpenGLFramebuffer.h/.cpp

  OpenGL帧缓冲区，继承Framebuffer，创建帧缓冲区，包括颜色缓冲区和深度缓冲区。

##### Layer文件

- Layer.h/.cpp

  所有层的基类，可接收事件并处理。

- LayerStack.h/.cpp

  存储所有层，普通层在列表前半部分，覆盖层在列表后半部分。

- ImGuiLayer.h/.cpp

  ImGui层，渲染ImGui。

##### Renderer

- GraphicsContext.h

  渲染上下文抽象类，可派生特定的图形API上下文接口。

- Shader.h/.cpp

  着色器，顶点着色器处理顶点，片元着色器处理像素，最终输出该像素的正确颜色。
  
- Renderer.h/.cpp

  渲染器接口。

- Buffer.h/.cpp

  缓冲抽象接口，可根据RendererAPI创建不同渲染接口的缓冲。缓冲区布局接口，格式化缓冲区布局。
  
- VertexArray.h/.cpp

  顶点数组接口，可根据RendererAPI创建不同渲染接口的顶点数组。整合缓冲布局。
  
- RendererAPI.h/.cpp

  渲染器抽象接口，派生出不同平台渲染器。

- RenderCommand.h/.cpp

  渲染命令，调用RenderAPI的方法，执行渲染指令。
  
- OrthographicCamera.h/.cpp

  正交相机，进行相机变换，包括计算正交投影矩阵、视图矩阵。
  
- Texture.h/.cpp

  抽象纹理接口，可派生不同渲染平台纹理接口。
  
- SubTexture2D.h/.cpp

  子纹理，根据子纹理坐标从Texture中裁剪。

- OrthographicCameraController.h/.cpp

  正交相机控制器，控制相机移动、旋转，窗口缩放。
  
- Renderer2D.h/.cpp

  2D渲染器。
  
- Framebuffer.h/.cpp

  帧缓冲区抽象接口。

##### Scene

- Scene.h/.cpp

  场景，包括所有的实体对象id。

- Components.h

  组件，所有组件。
  
- Entity.h/.cpp

  实体，场景中的物体（实际只保存id），通过id关联所有组件。
  
- Camera.h

  相机。

- SceneCamera.h/.cpp

  场景相机。
  
- ScriptableEntity.h

  可脚本化实体，所有本地脚本的基类。

### Hazel-Editor 项目

#### asserts

- ##### shaders

  着色器文件，包括顶点着色器和片元着色器。

- ##### textures

  贴图文件。

#### src

- HazelEditor.cpp

  编辑器，继承Application，构建应用程序或游戏。

- EditorLayer.h/.cpp

  编辑器层，构建引擎编辑器。

### Sandbox 项目

#### asserts

- ##### shaders

  着色器文件，包括顶点着色器和片元着色器。

- ##### textures

  贴图文件。

#### src

- SandboxApp.cpp

  应用程序类，继承Application。可创建具体Layer。
  
- Sandbox2D.h/.cpp

  2D渲染测试层，继承Layer。

## 子系统

### 日志系统

### 事件系统

### 输入系统

### 渲染系统

