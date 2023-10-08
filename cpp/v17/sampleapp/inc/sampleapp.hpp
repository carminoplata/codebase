#include <string>

using namespace std;

class SampleApp{
public:
    SampleApp() = default;
    SampleApp(const string& text);
    SampleApp(const SampleApp&& other);
    SampleApp& operator=(const SampleApp&& other);

    SampleApp(const SampleApp& other) = delete;
    SampleApp& operator=(const SampleApp& other) = delete;
    
    string getText() const;
    void print(ostream& os);

protected:
    
private:
    string text;
};