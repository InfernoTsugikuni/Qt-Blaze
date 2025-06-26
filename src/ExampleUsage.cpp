#include <QApplication>
#include "CustomWindow.h"

class MyWindow : public CustomWindowBase {
    Q_OBJECT
public:
    // Default constructor
    MyWindow(QWidget* parent = nullptr) : CustomWindowBase(parent) {
        setupUI();
    }
    
    // Constructor with config (this is what you're using)
    MyWindow(QWidget* parent, const WindowConfig& config) 
        : CustomWindowBase(parent, config) {
        setupUI();
    }

private:
    void setupUI() {
        // Your custom UI setup here
        // The title bar is already handled automatically
        
        // Example: Add content to the main area
        QWidget* contentWidget = new QWidget();
        contentWidget->setStyleSheet("background-color: transparent;");
        
        // Add your widgets to contentWidget here...
        
        // Get the central widget's layout and add your content
        QVBoxLayout* mainLayout = qobject_cast<QVBoxLayout*>(centralWidget()->layout());
        if (mainLayout) {
            mainLayout->insertWidget(1, contentWidget); // Insert after title bar
        }
    }
};

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);
    
    // Config
    WindowConfig config;
    // config.showTitleBar = false;  |  OPTIONAL - DISABLES THE TITLE BAR
    config.width = 800; // Window width
    config.height = 600; // Window height
    config.borderRadius = 25; // Window border radius
    config.backgroundColor = QColor("#1e1e1e"); // Window background color
    config.borderColor = QColor("#444"); // Window border color
    config.windowTitle = "My Custom App"; // Window title for the custom title bar
    config.titleTextColor = QColor("#00ff00"); // Window title color for the custom title bar
    config.titleBarColor = QColor("#333"); // Window title bar background color
    
    // Optional but reccomended - add custom button icons with your path, THEY MUST BE 18x18
    config.minimizeIcon = "assets/Minimize.png";
    config.minimizeHoverIcon = "assets/MinimizeHover.png";
    config.closeIcon = "assets/Close.png";
    config.closeHoverIcon = "assets/CloseHover.png";
    
    MyWindow customWindow(nullptr, config);
    customWindow.show();
    
    return app.exec();
}

#include "ExampleUsage.moc" // Required for Q_OBJECT in .cpp files