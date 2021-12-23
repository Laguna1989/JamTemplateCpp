#include "command_recorder.hpp"
#include "input/control_command_composite.hpp"
#include <gtest/gtest.h>

class ControlCommandCompositeTest : public ::testing::Test {
public:
    std::shared_ptr<CommandRecorder> recorder1 { nullptr };
    std::shared_ptr<CommandRecorder> recorder2 { nullptr };
    std::shared_ptr<jt::ControlCommandComposite> composite { nullptr };
    void SetUp() override
    {
        recorder1 = std::make_shared<CommandRecorder>();
        recorder2 = std::make_shared<CommandRecorder>();
        std::vector<std::shared_ptr<jt::ControlCommandInterface>> const vec { recorder1,
            recorder2 };
        composite = std::make_shared<jt::ControlCommandComposite>(vec);
    }
};

TEST_F(ControlCommandCompositeTest, ExecuteIsCalledForAllCommands)
{
    composite->execute(0.1f);
    ASSERT_TRUE(recorder1->m_executed);
    ASSERT_TRUE(recorder2->m_executed);
}

TEST_F(ControlCommandCompositeTest, ResetIsCalledForAllCommands)
{
    composite->execute(0.1f);
    composite->reset();
    ASSERT_TRUE(recorder1->m_reset);
    ASSERT_TRUE(recorder2->m_reset);
}
