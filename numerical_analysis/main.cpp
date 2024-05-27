// Dear ImGui: standalone example application for GLFW + OpenGL 3, using programmable pipeline
// (GLFW is a cross-platform general purpose library for handling windows, inputs, OpenGL/Vulkan/Metal graphics context creation, etc.)

// Learn about Dear ImGui:
// - FAQ                  https://dearimgui.com/faq
// - Getting Started      https://dearimgui.com/getting-started
// - Documentation        https://dearimgui.com/docs (same as your local docs/ folder).
// - Introduction, links and more at the top of imgui.cpp

#include "imgui/imgui.h"
#include "imgui/backends/imgui_impl_glfw.h"
#include "imgui/backends/imgui_impl_opengl3.h"
#include <stdio.h>
#define GL_SILENCE_DEPRECATION
#if defined(IMGUI_IMPL_OPENGL_ES2)
#include <GLES2/gl2.h>
#endif
#include <GLFW/glfw3.h> // Will drag system OpenGL headers
#include <iostream>
#include <dlfcn.h>

#include "interval.h"
#include "newton_raphson.h"

using std::string;
const int TXTMX = 1024;

// [Win32] Our example includes a copy of glfw3.lib pre-compiled with VS2010 to maximize ease of testing and compatibility with old VS compilers.
// To link with VS2010-era libraries, VS2015+ requires linking with legacy_stdio_definitions.lib, which we do using this pragma.
// Your own project should not be affected, as you are likely to link with a newer binary of GLFW that is adequate for your version of Visual Studio.
#if defined(_MSC_VER) && (_MSC_VER >= 1900) && !defined(IMGUI_DISABLE_WIN32_FUNCTIONS)
#pragma comment(lib, "legacy_stdio_definitions")
#endif

// This example can also compile and run with Emscripten! See 'Makefile.emscripten' for details.
#ifdef __EMSCRIPTEN__
#include "../libs/emscripten/emscripten_mainloop_stub.h"
#endif

static void glfw_error_callback(int error, const char* description)
{
    fprintf(stderr, "GLFW Error %d: %s\n", error, description);
}

//load f, df and d2f functions
template<typename T>
int read_fuct(string path, T (*&f)(T), T (*&df)(T), T (*&d2f)(T)){
    void* handle = dlopen(path.c_str(), RTLD_LAZY);
    if (!handle) {
        std::cerr << "Cannot load library: " << dlerror() << '\n';
        return 1;
    }

    string name;
    string suf = "";
    if (std::is_same<T, _Float128>::value){
        suf = "f";
    }
    
    name = "f" + suf;
    f = (T (*)(T))dlsym(handle, name.c_str());
    const char* dlsym_error = dlerror();
    if (dlsym_error) {
        std::cerr << "Cannot load symbol 'f': " << dlsym_error << '\n';
        dlclose(handle);
        return 2;
    }

    name = "df" + suf;
    df = (T (*)(T))dlsym(handle, name.c_str());
    dlsym_error = dlerror();
    if (dlsym_error) {
        std::cerr << "Cannot load symbol 'df': " << dlsym_error << '\n';
        dlclose(handle);
        return 2;
    }

    name = "d2f" + suf;
    d2f = (T (*)(T))dlsym(handle, name.c_str());
    dlsym_error = dlerror();
    if (dlsym_error) {
        std::cerr << "Cannot load symbol 'd2f': " << dlsym_error << '\n';
        dlclose(handle);
        return 2;
    }
    return 0;
}

// Main code
int main(int, char**)
{
    glfwSetErrorCallback(glfw_error_callback);
    if (!glfwInit())
        return 1;

    // Decide GL+GLSL versions
#if defined(IMGUI_IMPL_OPENGL_ES2)
    // GL ES 2.0 + GLSL 100
    const char* glsl_version = "#version 100";
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 2);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);
    glfwWindowHint(GLFW_CLIENT_API, GLFW_OPENGL_ES_API);
#elif defined(__APPLE__)
    // GL 3.2 + GLSL 150
    const char* glsl_version = "#version 150";
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 2);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);  // 3.2+ only
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);            // Required on Mac
#else
    // GL 3.0 + GLSL 130
    const char* glsl_version = "#version 130";
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);
    //glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);  // 3.2+ only
    //glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);            // 3.0+ only
#endif

    // Create window with graphics context
    GLFWwindow* window = glfwCreateWindow(1280, 720, "Dear ImGui GLFW+OpenGL3 example", nullptr, nullptr);
    if (window == nullptr)
        return 1;
    glfwMakeContextCurrent(window);
    glfwSwapInterval(1); // Enable vsync

    // Setup Dear ImGui context
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO(); (void)io;
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;     // Enable Keyboard Controls
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;      // Enable Gamepad Controls

    // Setup Dear ImGui style
    ImGui::StyleColorsDark();
    //ImGui::StyleColorsLight();

    // Setup Platform/Renderer backends
    ImGui_ImplGlfw_InitForOpenGL(window, true);
#ifdef __EMSCRIPTEN__
    ImGui_ImplGlfw_InstallEmscriptenCanvasResizeCallback("#canvas");
#endif
    ImGui_ImplOpenGL3_Init(glsl_version);

    // Load Fonts
    // - If no fonts are loaded, dear imgui will use the default font. You can also load multiple fonts and use ImGui::PushFont()/PopFont() to select them.
    // - AddFontFromFileTTF() will return the ImFont* so you can store it if you need to select the font among multiple.
    // - If the file cannot be loaded, the function will return a nullptr. Please handle those errors in your application (e.g. use an assertion, or display an error and quit).
    // - The fonts will be rasterized at a given size (w/ oversampling) and stored into a texture when calling ImFontAtlas::Build()/GetTexDataAsXXXX(), which ImGui_ImplXXXX_NewFrame below will call.
    // - Use '#define IMGUI_ENABLE_FREETYPE' in your imconfig file to use Freetype for higher quality font rendering.
    // - Read 'docs/FONTS.md' for more instructions and details.
    // - Remember that in C/C++ if you want to include a backslash \ in a string literal you need to write a double backslash \\ !
    // - Our Emscripten build process allows embedding fonts to be accessible at runtime from the "fonts/" folder. See Makefile.emscripten for details.
    //io.Fonts->AddFontDefault();
    //io.Fonts->AddFontFromFileTTF("c:\\Windows\\Fonts\\segoeui.ttf", 18.0f);
    //io.Fonts->AddFontFromFileTTF("../../misc/fonts/DroidSans.ttf", 16.0f);
    //io.Fonts->AddFontFromFileTTF("../../misc/fonts/Roboto-Medium.ttf", 16.0f);
    //io.Fonts->AddFontFromFileTTF("../../misc/fonts/Cousine-Regular.ttf", 15.0f);
    //ImFont* font = io.Fonts->AddFontFromFileTTF("c:\\Windows\\FonPts\\ArialUni.ttf", 18.0f, nullptr, io.Fonts->GetGlyphRangesJapanese());
    //IM_ASSERT(font != nullptr);

    // Our state
    ImVec4 clear_color = ImVec4(0.45f, 0.55f, 0.60f, 1.00f);
    static char path[TXTMX] = "/home/msjtw/Documents/uni/numerical_analysis/ext/libext.so";
    string libraryPath;
    static int load_status = -1;
    int calc_type = 0;
    static char x[TXTMX], mit[TXTMX], eps[TXTMX], xupper[TXTMX], xlower[TXTMX], epslower[TXTMX];
    Interval (*f)(Interval);
    Interval (*df)(Interval);
    Interval (*d2f)(Interval);
    _Float128 (*ff)(_Float128);
    _Float128 (*dff)(_Float128);
    _Float128 (*d2ff)(_Float128);
    int stat = -1;
    Interval fx;
    Interval fatx;
    _Float128 ffx;
    _Float128 ffatx;
    int imit;
    
    // Main loop
#ifdef __EMSCRIPTEN__
    // For an Emscripten build we are disabling file-system access, so let's not attempt to do a fopen() of the imgui.ini file.
    // You may manually call LoadIniSettingsFromMemory() to load settings from your own storage.
    io.IniFilename = nullptr;
    EMSCRIPTEN_MAINLOOP_BEGIN
#else
    while (!glfwWindowShouldClose(window))
#endif
    {
        // Poll and handle events (inputs, window resize, etc.)
        // You can read the io.WantCaptureMouse, io.WantCaptureKeyboard flags to tell if dear imgui wants to use your inputs.
        // - When io.WantCaptureMouse is true, do not dispatch mouse input data to your main application, or clear/overwrite your copy of the mouse data.
        // - When io.WantCaptureKeyboard is true, do not dispatch keyboard input data to your main application, or clear/overwrite your copy of the keyboard data.
        // Generally you may always pass all inputs to dear imgui, and hide them from your application based on those two flags.
        glfwPollEvents();

        // Start the Dear ImGui frame
        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();

        // 1. Show the big demo window (Most of the sample code is in ImGui::ShowDemoWindow()! You can browse its code to learn more about Dear ImGui!).
        // if (show_demo_window)
        //     ImGui::ShowDemoWindow(&show_demo_window);

        // 2. Show a simple window that we create ourselves. We use a Begin/End pair to create a named window.
        {
            static bool use_work_area = true;
            const ImGuiViewport* viewport = ImGui::GetMainViewport();
            ImGui::SetNextWindowPos(use_work_area ? viewport->WorkPos : viewport->Pos);
            ImGui::SetNextWindowSize(use_work_area ? viewport->WorkSize : viewport->Size);
            ImGui::Begin("Newton Raphson", NULL, ImGuiWindowFlags_NoCollapse|ImGuiWindowFlags_NoMove);                          // Create a window called "Hello, world!" and append into it.
            ImGui::SeparatorText("Library path");
            ImGui::InputTextWithHint("##", "enter path to library containg functions", path, IM_ARRAYSIZE(path));
            ImGui::SameLine();
            if (ImGui::Button("Load")){
                libraryPath = path;
                load_status = read_fuct<Interval>(libraryPath, f, df, d2f);
                load_status = read_fuct<_Float128>(libraryPath, ff, dff, d2ff);
            }
            if (load_status >= 0)
            {
                string text;
                if(load_status == 0){
                    text = "Loaded";
                    ImGui::TextColored(ImVec4(0.0f, 1.0f, 0.0f, 1.0f), text.c_str());
                    // if (ImGui::TreeNode("Plotting")){
                    //     static int display_count = 70;
                    //     struct Funcs{
                    //         static float func(void*, int i) { return ff(i); }
                    //     };
                    //     ImGui::PlotLines("Lines", Funcs::func, NULL, display_count, 0, NULL, -1.0f, 1.0f, ImVec2(0, 80));
                    //     ImGui::TreePop();
                    // }
                }
                else if(load_status == 1){
                    text = "Cannot find: " + string(libraryPath);
                    ImGui::TextColored(ImVec4(1.0f, 0.0f, 0.0f, 1.0f), text.c_str());
                }
                else{
                    text = "Cannot load function symbol";
                    ImGui::TextColored(ImVec4(1.0f, 0.0f, 0.0f, 1.0f), text.c_str());
                }
            }

            if(load_status == 0){
                ImGui::SeparatorText("Calculation Type");

                ImGui::RadioButton("Float", &calc_type, 1); ImGui::SameLine();
                ImGui::RadioButton("Point Interval", &calc_type, 2); ImGui::SameLine();
                ImGui::RadioButton("Interval", &calc_type, 3);


                if(calc_type == 1){
                    ImGui::Text("Float");
                    ImGui::Text("x");
                    ImGui::SameLine(ImGui::GetFontSize() * 22);
                    ImGui::Text("max number of iterations");
                    ImGui::SameLine(ImGui::GetFontSize() * 42);
                    ImGui::Text("epsilon");
                    ImGui::SetNextItemWidth(ImGui::GetFontSize() * 20);
                    ImGui::InputTextWithHint("##x", "x", x, IM_ARRAYSIZE(x)); ImGui::SameLine();
                    ImGui::SetNextItemWidth(ImGui::GetFontSize() * 20);
                    ImGui::InputTextWithHint("##mit", "max number of iterations", mit, IM_ARRAYSIZE(mit)); ImGui::SameLine();
                    ImGui::SetNextItemWidth(ImGui::GetFontSize() * 20);
                    ImGui::InputTextWithHint("##eps", "desired epsilon", eps, IM_ARRAYSIZE(eps));
                    string sx(x);
                    string smit(mit);
                    string seps(eps);

                    int it;

                    if (ImGui::Button("Calculate") and !sx.empty() and !smit.empty() and !seps.empty()){
                        ffx = strtof128(x, NULL);
                        _Float128 feps = strtof128(eps, NULL);
                        imit = std::stoi(string(mit));
                        stat = newton_raphson_f(ffx, ff, dff, d2ff, imit, feps, ffatx, it);
                    }
                    if(stat == 0){
                        string res = to_string(ffx);
                        string stringstate;
                        stringstate = std::to_string(stat);
                        ImGui::Text("return status: "); ImGui::SameLine();
                        ImGui::Text(stringstate.c_str()); ImGui::SameLine();
                        ImGui::TextColored(ImVec4(0.0f, 1.0f, 0.0f, 1.0f), "Ok");
                        ImGui::Text("x:    "); ImGui::SameLine();
                        ImGui::Text(res.c_str());
                        ImGui::Text("f(x): "); ImGui::SameLine();
                        string sfatx = to_string(ffatx);
                        ImGui::Text(sfatx.c_str());
                        ImGui::Text("iterations: "); ImGui::SameLine();
                        string sit = std::to_string(it);
                        ImGui::Text(sit.c_str());
                    }
                    if(stat == 3){
                        string res = to_string(ffx);
                        string stringstate;
                        stringstate = std::to_string(stat);
                        ImGui::Text("return status: "); ImGui::SameLine();
                        ImGui::Text(stringstate.c_str()); ImGui::SameLine();
                        std::string mess = "Could not reach desired accuracy in " + std::to_string(imit) + " iterations.";
                        ImGui::TextColored(ImVec4(1.0f, 1.0f, 0.0f, 1.0f) , mess.c_str());
                        ImGui::Text("x:    "); ImGui::SameLine();
                        ImGui::Text(res.c_str());
                        ImGui::Text("f(x): "); ImGui::SameLine();
                        string sfatx = to_string(ffatx);
                        ImGui::Text(sfatx.c_str());
                        ImGui::Text("iterations: "); ImGui::SameLine();
                        string sit = std::to_string(it);
                        ImGui::Text(sit.c_str());
                    }
                    if(stat == 1){
                        string stringstate;
                        stringstate = std::to_string(stat);
                        ImGui::Text("return status: "); ImGui::SameLine();
                        ImGui::Text(stringstate.c_str()); ImGui::SameLine();
                        std::string mess = "Error! The maximal number of iterations is lower than 1.";
                        ImGui::TextColored(ImVec4(1.0f, 0.0f, 0.0f, 1.0f) , mess.c_str());
                    }
                    if(stat == 2){
                        string stringstate;
                        stringstate = std::to_string(stat);
                        ImGui::Text("return status: "); ImGui::SameLine();
                        ImGui::Text(stringstate.c_str()); ImGui::SameLine();
                        std::string mess = "Error! For some x: f\"(x) = 0.";
                        ImGui::TextColored(ImVec4(1.0f, 0.0f, 0.0f, 1.0f) , mess.c_str());
                    }
                    if(stat == 4){
                        string stringstate;
                        stringstate = std::to_string(stat);
                        ImGui::Text("return status: "); ImGui::SameLine();
                        ImGui::Text(stringstate.c_str()); ImGui::SameLine();
                        std::string mess = "Error! For some x: [f'(x)]² -2f(x)f\"(x) < 0";
                        ImGui::TextColored(ImVec4(1.0f, 0.0f, 0.0f, 1.0f) , mess.c_str());
                    }
                }
                else if(calc_type == 2){
                    ImGui::Text("Point Interval");
                    ImGui::Text("x");
                    ImGui::SameLine(ImGui::GetFontSize() * 22);
                    ImGui::Text("max number of iterations");
                    ImGui::SameLine(ImGui::GetFontSize() * 42);
                    ImGui::Text("epsilon");
                    ImGui::SetNextItemWidth(ImGui::GetFontSize() * 20);
                    ImGui::InputTextWithHint("##xi", "x", x, IM_ARRAYSIZE(path)); ImGui::SameLine();
                    ImGui::SetNextItemWidth(ImGui::GetFontSize() * 20);
                    ImGui::InputTextWithHint("##miti", "max number of iterations", mit, IM_ARRAYSIZE(path)); ImGui::SameLine();
                    ImGui::SetNextItemWidth(ImGui::GetFontSize() * 20);
                    ImGui::InputTextWithHint("##epsi", "desired epsilon", eps, IM_ARRAYSIZE(path));
                    string sx(x);
                    string smit(mit);
                    string seps(eps);

                    int it;

                    if (ImGui::Button("Calculate") and !sx.empty() and !smit.empty() and !seps.empty()){
                        fx.read_float(sx);
                        _Float128 feps = strtof128(eps, NULL);
                        imit = std::stoi(string(mit));
                        stat = newton_raphson_i(fx, f, df, d2f, imit, feps, fatx, it);
                    }
                    if(stat == 0){
                        string res = to_string(fx);
                        string stringstate;
                        stringstate = std::to_string(stat);
                        ImGui::Text("return status: "); ImGui::SameLine();
                        ImGui::Text(stringstate.c_str()); ImGui::SameLine();
                        ImGui::TextColored(ImVec4(0.0f, 1.0f, 0.0f, 1.0f), "Ok");
                        ImGui::Text("x:    "); ImGui::SameLine();
                        ImGui::Text(res.c_str());
                        ImGui::Text("f(x): "); ImGui::SameLine();
                        string sfatx = to_string(fatx);
                        ImGui::Text(sfatx.c_str());
                        ImGui::Text("iterations: "); ImGui::SameLine();
                        string sit = std::to_string(it);
                        ImGui::Text(sit.c_str());
                    }
                    if(stat == 3){
                        string res = to_string(fx);
                        string stringstate;
                        stringstate = std::to_string(stat);
                        ImGui::Text("return status: "); ImGui::SameLine();
                        ImGui::Text(stringstate.c_str()); ImGui::SameLine();
                        std::string mess = "Could not reach desired accuracy in " + std::to_string(imit) + " iterations.";
                        ImGui::TextColored(ImVec4(1.0f, 1.0f, 0.0f, 1.0f) , mess.c_str());
                        ImGui::Text("x:    "); ImGui::SameLine();
                        ImGui::Text(res.c_str());
                        ImGui::Text("f(x): "); ImGui::SameLine();
                        string sfatx = to_string(fatx);
                        ImGui::Text(sfatx.c_str());
                        ImGui::Text("iterations: "); ImGui::SameLine();
                        string sit = std::to_string(it);
                        ImGui::Text(sit.c_str());
                    }
                    if(stat == 1){
                        string stringstate;
                        stringstate = std::to_string(stat);
                        ImGui::Text("return status: "); ImGui::SameLine();
                        ImGui::Text(stringstate.c_str()); ImGui::SameLine();
                        std::string mess = "Error! The maximal number of iterations is lower than 1.";
                        ImGui::TextColored(ImVec4(1.0f, 0.0f, 0.0f, 1.0f) , mess.c_str());
                    }
                    if(stat == 2){
                        string stringstate;
                        stringstate = std::to_string(stat);
                        ImGui::Text("return status: "); ImGui::SameLine();
                        ImGui::Text(stringstate.c_str()); ImGui::SameLine();
                        std::string mess = "Error! For some x: f\"(x) = 0.";
                        ImGui::TextColored(ImVec4(1.0f, 0.0f, 0.0f, 1.0f) , mess.c_str());
                    }
                    if(stat == 4){
                        string stringstate;
                        stringstate = std::to_string(stat);
                        ImGui::Text("return status: "); ImGui::SameLine();
                        ImGui::Text(stringstate.c_str()); ImGui::SameLine();
                        std::string mess = "Error! For some x: [f'(x)]² -2f(x)f\"(x) < 0";
                        ImGui::TextColored(ImVec4(1.0f, 0.0f, 0.0f, 1.0f) , mess.c_str());
                    }
                }
                else if(calc_type == 3){
                    ImGui::Text("Interval");
                    ImGui::Text("x");
                    ImGui::SameLine(ImGui::GetFontSize() * 22);
                    ImGui::Text("max number of iterations");
                    ImGui::SameLine(ImGui::GetFontSize() * 42);
                    ImGui::Text("epsilon");
                    ImGui::SetNextItemWidth(ImGui::GetFontSize() * 20);
                    ImGui::InputTextWithHint("##xii1", "x upper", xupper, IM_ARRAYSIZE(path)); ImGui::SameLine();
                    ImGui::SetNextItemWidth(ImGui::GetFontSize() * 20);
                    ImGui::InputTextWithHint("##mitii", "max number of iterations", mit, IM_ARRAYSIZE(path));  ImGui::SameLine();
                    ImGui::SetNextItemWidth(ImGui::GetFontSize() * 20);
                    ImGui::InputTextWithHint("##epsii", "desired epsilon", eps, IM_ARRAYSIZE(path));
                    ImGui::SetNextItemWidth(ImGui::GetFontSize() * 20);
                    ImGui::InputTextWithHint("##xii22", "x lower", xlower, IM_ARRAYSIZE(path)); 
                    // ImGui::SameLine();
                    // ImGui::SetNextItemWidth(ImGui::GetFontSize() * 20);
                    // ImGui::InputTextWithHint("##xii222", "epsilon lower", epslower, IM_ARRAYSIZE(path));
                    string sxu(xupper);
                    string sxl(xlower);
                    string smit(mit);
                    string seps(eps);
                    string sepsl(epslower);

                    int it;

                    if (ImGui::Button("Calculate") and !sxu.empty() and !sxl.empty() and !smit.empty() and !seps.empty()){
                        fx.read_interval(sxu, sxl);
                        _Float128 feps = strtof128(eps, NULL);
                        imit = std::stoi(string(mit));
                        stat = newton_raphson_i(fx, f, df, d2f, imit, feps, fatx, it);
                    }
                    if(stat == 0){
                        string res = to_string(fx);
                        string stringstate;
                        stringstate = std::to_string(stat);
                        ImGui::Text("return status: "); ImGui::SameLine();
                        ImGui::Text(stringstate.c_str()); ImGui::SameLine();
                        ImGui::TextColored(ImVec4(0.0f, 1.0f, 0.0f, 1.0f), "Ok");
                        ImGui::Text("x:    "); ImGui::SameLine();
                        ImGui::Text(res.c_str());
                        ImGui::Text("f(x): "); ImGui::SameLine();
                        string sfatx = to_string(fatx);
                        ImGui::Text(sfatx.c_str());
                        ImGui::Text("iterations: "); ImGui::SameLine();
                        string sit = std::to_string(it);
                        ImGui::Text(sit.c_str());
                    }
                    if(stat == 3){
                        string res = to_string(fx);
                        string stringstate;
                        stringstate = std::to_string(stat);
                        ImGui::Text("return status: "); ImGui::SameLine();
                        ImGui::Text(stringstate.c_str()); ImGui::SameLine();
                        std::string mess = "Could not reach desired accuracy in " + std::to_string(imit) + " iterations.";
                        ImGui::TextColored(ImVec4(1.0f, 1.0f, 0.0f, 1.0f) , mess.c_str());
                        ImGui::Text("x:    "); ImGui::SameLine();
                        ImGui::Text(res.c_str());
                        ImGui::Text("f(x): "); ImGui::SameLine();
                        string sfatx = to_string(fatx);
                        ImGui::Text(sfatx.c_str());
                        ImGui::Text("iterations: "); ImGui::SameLine();
                        string sit = std::to_string(it);
                        ImGui::Text(sit.c_str());
                    }
                    if(stat == 1){
                        string stringstate;
                        stringstate = std::to_string(stat);
                        ImGui::Text("return status: "); ImGui::SameLine();
                        ImGui::Text(stringstate.c_str()); ImGui::SameLine();
                        std::string mess = "Error! The maximal number of iterations is lower than 1.";
                        ImGui::TextColored(ImVec4(1.0f, 0.0f, 0.0f, 1.0f) , mess.c_str());
                    }
                    if(stat == 2){
                        string stringstate;
                        stringstate = std::to_string(stat);
                        ImGui::Text("return status: "); ImGui::SameLine();
                        ImGui::Text(stringstate.c_str()); ImGui::SameLine();
                        std::string mess = "Error! For some x: f\"(x) = 0.";
                        ImGui::TextColored(ImVec4(1.0f, 0.0f, 0.0f, 1.0f) , mess.c_str());
                    }
                    if(stat == 4){
                        string stringstate;
                        stringstate = std::to_string(stat);
                        ImGui::Text("return status: "); ImGui::SameLine();
                        ImGui::Text(stringstate.c_str()); ImGui::SameLine();
                        std::string mess = "Error! For some x: [f'(x)]² -2f(x)f\"(x) < 0";
                        ImGui::TextColored(ImVec4(1.0f, 0.0f, 0.0f, 1.0f) , mess.c_str());
                    }
                }
            }
            ImGui::End();
        }


        // Rendering
        ImGui::Render();
        int display_w, display_h;
        glfwGetFramebufferSize(window, &display_w, &display_h);
        glViewport(0, 0, display_w, display_h);
        glClearColor(clear_color.x * clear_color.w, clear_color.y * clear_color.w, clear_color.z * clear_color.w, clear_color.w);
        glClear(GL_COLOR_BUFFER_BIT);
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

        glfwSwapBuffers(window);
    }
#ifdef __EMSCRIPTEN__
    EMSCRIPTEN_MAINLOOP_END;
#endif

    // Cleanup
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();

    glfwDestroyWindow(window);
    glfwTerminate();

    return 0;
}
