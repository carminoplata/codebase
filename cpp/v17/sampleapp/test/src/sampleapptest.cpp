#include "sampleapptest.hpp"
#include "sampleapp.hpp"

SampleAppFixture::SampleAppFixture()
{
}

TEST_F(SampleAppFixture, DefaultSampleApp)
{
    SampleApp app;

    EXPECT_EQ(app.getText(), expectedText);
}

TEST_F(SampleAppFixture, SampleAppHelloWorld)
{
    SampleApp app("Hello World!");
    expectedText = "Hello World!"; 
    EXPECT_EQ(app.getText(), expectedText);
}

TEST_F(SampleAppFixture, SampleAppHelloWorldNumbers)
{
    SampleApp app("Hello World 100!");
    expectedText = "Hello World 100!"; 
    EXPECT_EQ(app.getText(), expectedText);
}

TEST_F(SampleAppFixture, CreateSampleAppByMovement)
{
    SampleApp app("Hello World 100!");
    expectedText = "Hello World 100!"; 
    SampleApp newApp(std::move(app));
    EXPECT_EQ(newApp.getText(), expectedText);
}

TEST_F(SampleAppFixture, AssignSampleAppByMovement)
{
    SampleApp app("Hello World 100!");
    expectedText = "Hello World 100!"; 
    SampleApp newApp = std::move(app);
    EXPECT_EQ(newApp.getText(), expectedText);
}

TEST_F(SampleAppFixture, SampleAppPrintText)
{
    SampleApp app("Hello World 100!");
    expectedText = "Hello World 100!\n"; 
    std::ostringstream os;
    app.print(os);
    EXPECT_EQ(os.str(), expectedText);
}