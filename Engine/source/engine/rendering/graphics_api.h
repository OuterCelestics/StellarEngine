class GraphicsAPI {
public:
    virtual void Initialize() = 0;
    virtual void Render() = 0;
    virtual void Terminate() = 0;
};