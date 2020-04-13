@echo off
sokol-shdc.exe -i app.glsl -o glcore330.h --slang glsl330
sokol-shdc.exe -i app.glsl -o gles2.h --slang glsl100
sokol-shdc.exe -i app.glsl -o gles3.h --slang glsl300es
sokol-shdc.exe -i app.glsl -o d3d11.h --slang hlsl5
sokol-shdc.exe -i app.glsl -o ios.h --slang metal_ios
