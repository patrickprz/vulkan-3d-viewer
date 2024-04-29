class VulkanHelper{
    public:
        void run();
    private:
        void initWindow();
        void initVulkan();
        void mainLoop();
        void cleanup();
};