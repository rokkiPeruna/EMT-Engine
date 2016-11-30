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
			
			../../../../../../source/Core/EngineObject.cpp
			../../../../../../source/Core/Scene.cpp
			../../../../../../source/Core/Settings.cpp
			../../../../../../source/Core/Timer.cpp

			../../../../../../source/EntityComponentSystem/Components/Component.cpp
			../../../../../../source/EntityComponentSystem/Components/CollisionComponent.cpp
			../../../../../../source/EntityComponentSystem/Components/RenderComponent.cpp
			../../../../../../source/EntityComponentSystem/Components/ShaderComponent.cpp
			../../../../../../source/EntityComponentSystem/Components/ShapeComponent.cpp
			../../../../../../source/EntityComponentSystem/Components/TextureComponent.cpp
			../../../../../../source/EntityComponentSystem/Components/TransformComponent.cpp

			../../../../../../source/EntityComponentSystem/Entity/Entity.cpp

			../../../../../../source/EntityComponentSystem/Systems/System.cpp
			../../../../../../source/EntityComponentSystem/Systems/CollisionSystem.cpp
			../../../../../../source/EntityComponentSystem/Systems/RenderSystem.cpp
			../../../../../../source/EntityComponentSystem/Systems/ShaderSystem.cpp
			../../../../../../source/EntityComponentSystem/Systems/ShapeSystem.cpp
			../../../../../../source/EntityComponentSystem/Systems/TextureSystem.cpp
			../../../../../../source/EntityComponentSystem/Systems/Transform.cpp

			#../../../../../../source/IO_Manager/Android/stuffHere
			
			../../../../../../source/Texture/Shape.cpp

            ../../../../../../source/Utility/Assert.cpp
			../../../../../../source/Utility/FileHandler.cpp
			../../../../../../source/Utility/Messenger.cpp
			
			../../../../../../source/Window/Window.cpp
			../../../../../../source/Window/AndroidWindow.cpp
			
            main.cpp)

target_include_directories(native-activity PRIVATE
							../../../../../../include
                           ${ANDROID_NDK}/sources/android/native_app_glue)

# add lib dependencies
target_link_libraries(native-activity
                      android
                      app-glue
                      EGL
                      GLESv2
                      log)
