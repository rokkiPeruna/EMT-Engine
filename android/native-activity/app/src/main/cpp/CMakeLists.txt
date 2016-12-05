#
# Copyright (C) The Android Open Source Project
#
# Licensed under the Apache License, Version 2.0 (the "License");
# you may not use this file except in compliance with the License.
# You may obtain a copy of the License at
#
#      http://www.apache.org/licenses/LICENSE-2.0
#
# Unless required by applicable law or agreed to in writing, software
# distributed under the License is distributed on an "AS IS" BASIS,
# WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
# See the License for the specific language governing permissions and
# limitations under the License.
#

cmake_minimum_required(VERSION 3.4.1)

# build native_app_glue as a static lib
add_library(app-glue STATIC
            ${ANDROID_NDK}/sources/android/native_app_glue/android_native_app_glue.c)

# now build app's shared lib
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=gnu++11")

add_library(native-activity SHARED
            #main.cpp
            JEJ_Android_Main.cpp
            ../../../../../../source/Core/EngineObject.cpp
            ../../../../../../source/Core/Scene.cpp
            ../../../../../../source/Core/Settings.cpp
            ../../../../../../source/Core/Timer.cpp

            ../../../../../../source/Core/AndroidAppState.cpp

            ../../../../../../source/EntityComponentSys/Entity/Entity.cpp

            ../../../../../../source/EntityComponentSys/Components/Component.cpp
            #../../../../../../source/EntityComponentSys/Components/CollisionComponent.cpp
            ../../../../../../source/EntityComponentSys/Components/RenderComponent.cpp
            ../../../../../../source/EntityComponentSys/Components/ShaderComponent.cpp
            ../../../../../../source/EntityComponentSys/Components/ShapeComponent.cpp
            ../../../../../../source/EntityComponentSys/Components/TextureComponent.cpp
            ../../../../../../source/EntityComponentSys/Components/TransformComponent.cpp



            ../../../../../../source/EntityComponentSys/Systems/System.cpp
            ../../../../../../source/EntityComponentSys/Systems/CollisionSystem.cpp
            ../../../../../../source/EntityComponentSys/Systems/RenderSystem.cpp
            ../../../../../../source/EntityComponentSys/Systems/ShaderSystem.cpp
            ../../../../../../source/EntityComponentSys/Systems/ShapeSystem.cpp
            ../../../../../../source/EntityComponentSys/Systems/TextureSystem.cpp
            ../../../../../../source/EntityComponentSys/Systems/TransformSystem.cpp

            ../../../../../../source/IO_Manager/Android/InputManager.cpp

            ../../../../../../source/Texture/Shape.cpp

            ../../../../../../source/Utility/Assert.cpp
            ../../../../../../source/Utility/FileHandler.cpp
            ../../../../../../source/Utility/Messenger.cpp

            ../../../../../../source/Window/Window.cpp
            ../../../../../../source/Window/AndroidWindow.cpp
            )

target_include_directories(native-activity PRIVATE
                            ../../../../../../include
                            ../../../../../../include/External
                           ${ANDROID_NDK}/sources/android/native_app_glue)

# add lib dependencies
target_link_libraries(native-activity
                      android
                      app-glue
                      EGL
                      GLESv2
                      log)
