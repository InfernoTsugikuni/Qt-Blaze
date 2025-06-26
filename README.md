# Qt Custom Window Library

A modern Qt library for creating frameless windows with rounded corners and draggable title bars. Perfect for creating sleek desktop applications with a custom look and feel.

## Features

- ✅ **Frameless Windows** - Clean, modern appearance without system window decorations
- ✅ **Rounded Corners** - Smooth, anti-aliased rounded window borders
- ✅ **Draggable Title Bar** - Built-in window dragging functionality
- ✅ **Custom Button Icons** - Use your own minimize/close button assets
- ✅ **Fully Configurable** - Colors, sizes, borders, and styling through simple config struct
- ✅ **Optional Title Bar** - Can be disabled for completely custom windows
- ✅ **Cross-Platform** - Works on Windows, macOS, and Linux
- ✅ **Easy Integration** - Single header file, just inherit and go!

## Quick Start

> 💡 **Want to see it in action?** Check out the complete example in [`./src/ExampleUsage.cpp`](./src/ExampleUsage.cpp) for a sleek, ready-to-run implementation!

### 1. Include the Header
```cpp
#include "CustomWindow.h"
```

### 2. Create Your Window Class
```cpp
class MyWindow : public CustomWindowBase {
    Q_OBJECT
public:
    MyWindow(QWidget* parent = nullptr) : CustomWindowBase(parent) {
        setupUI();
    }
    
    MyWindow(QWidget* parent, const WindowConfig& config) 
        : CustomWindowBase(parent, config) {
        setupUI();
    }

private:
    void setupUI() {
        // Add your custom widgets here
    }
};
```

### 3. Configure and Show
```cpp
int main(int argc, char *argv[]) {
    QApplication app(argc, argv);
    
    WindowConfig config;
    config.width = 800;
    config.height = 600;
    config.windowTitle = "My Custom App";
    config.backgroundColor = QColor("#1e1e1e");
    config.borderColor = QColor("#444");
    
    MyWindow window(nullptr, config);
    window.show();
    
    return app.exec();
}
```

## Configuration Options

The `WindowConfig` struct provides extensive customization options:

### Window Properties
```cpp
WindowConfig config;
config.width = 800;                              // Window width
config.height = 600;                             // Window height
config.borderRadius = 15;                        // Corner radius (pixels)
config.borderWidth = 1;                          // Border thickness
config.fixedSize = false;                        // Whether window is resizable
```

### Colors & Styling
```cpp
config.backgroundColor = QColor("#333");         // Main window background
config.borderColor = QColor("#757575");          // Window border color
config.titleBarColor = QColor("#242424");        // Title bar background
config.titleTextColor = QColor("#ff6b00");       // Title text color
config.titleFontSize = "16px";                   // Title font size
```

### Title Bar Settings
```cpp
config.showTitleBar = true;                      // Enable/disable title bar
config.windowTitle = "Custom Window";            // Window title text
config.titleBarHeight = 30;                      // Title bar height
```

### Custom Button Icons
```cpp
// Icons must be 18x18 pixels
config.minimizeIcon = "assets/Minimize.png";
config.minimizeHoverIcon = "assets/MinimizeHover.png";
config.closeIcon = "assets/Close.png";
config.closeHoverIcon = "assets/CloseHover.png";
```

## Advanced Usage

### Disable Title Bar
For completely custom windows:
```cpp
WindowConfig config;
config.showTitleBar = false;
MyWindow window(nullptr, config);
```

### Access Title Bar
```cpp
CustomTitleBar* titleBar = window.getTitleBar();
if (titleBar) {
    // Customize title bar further
}
```

### Change Title Dynamically
```cpp
window.setWindowTitle("New Title");
```

## Example Configurations

### Dark Theme
```cpp
WindowConfig darkConfig;
darkConfig.backgroundColor = QColor("#1e1e1e");
darkConfig.borderColor = QColor("#444");
darkConfig.titleBarColor = QColor("#2d2d2d");
darkConfig.titleTextColor = QColor("#ffffff");
```

### Gaming Style
```cpp
WindowConfig gameConfig;
gameConfig.backgroundColor = QColor("#0a0a0a");
gameConfig.borderColor = QColor("#00ff00");
gameConfig.titleBarColor = QColor("#1a1a1a");
gameConfig.titleTextColor = QColor("#00ff00");
gameConfig.borderRadius = 8;
```

### Minimal Style
```cpp
WindowConfig minimalConfig;
minimalConfig.backgroundColor = QColor("#ffffff");
minimalConfig.borderColor = QColor("#e0e0e0");
minimalConfig.titleBarColor = QColor("#f5f5f5");
minimalConfig.titleTextColor = QColor("#333333");
minimalConfig.borderRadius = 4;
```

## Requirements

- Qt 5.12 or higher
- C++11 or higher
- CMake 3.16+ (if using CMake)

## Installation

### Method 1: Copy Files
1. Copy `CustomWindow.h` to your project
2. Include it in your source files
3. Make sure to include the `.moc` file for Q_OBJECT classes

### Method 2: CMake Integration
```cmake
# Add to your CMakeLists.txt
add_executable(your_app main.cpp CustomWindow.h)
target_link_libraries(your_app Qt5::Widgets)
```

## Button Icon Guidelines

For best results with custom button icons:
- **Size**: Exactly 18x18 pixels
- **Format**: PNG with transparency
- **Style**: Match your app's design theme
- **Hover**: Provide hover variants for better UX

## Troubleshooting

### Window Not Showing
- Ensure you call `window.show()`
- Check that Qt application loop is running (`app.exec()`)

### Icons Not Loading
- Verify file paths are correct
- Ensure icons are 18x18 pixels
- Check file permissions and accessibility

### Build Errors with Q_OBJECT
- Include the `.moc` file: `#include "filename.moc"`
- Or move Q_OBJECT classes to separate header files

## Contributing

Contributions are welcome! Please feel free to submit pull requests or open issues for bugs and feature requests.

## License

This project is licensed under the MIT License - see the LICENSE file for details.

## Acknowledgments

- Inspired by modern application design trends
- Built with Qt's powerful widget system
- Designed for developer ease-of-use