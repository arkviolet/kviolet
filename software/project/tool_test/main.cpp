

#include <kviolet/kviolet.h>
#include <kviolet_3rd/kviolet_3rd.h>

using namespace kviolet::timer;
using namespace kviolet::timestamp;

int main(int argc, char** argv) {
  (void)argc;
  (void)argv;

  /// pulseaudio
  {
    int volume = 50;
    std::string audio_path = "./test.wav";
    auto taskid = std::to_string(Timestamp::MonotonicMilliseconds());
    auto pulseaudio = std::make_shared<kviolet::PulseAudioManager>();
    pulseaudio->Play(taskid, audio_path, volume);
    pulseaudio->Pause(taskid);
    pulseaudio->Resume(taskid);
    pulseaudio->Cancel();
    pulseaudio = nullptr;
  }

  /// gst audio
  {
    int volume = 50;
    std::string audio_path = "./test.wav";  ///*.wav *.mp3
    auto taskid = std::to_string(Timestamp::MonotonicMilliseconds());
    auto gst = std::make_shared<kviolet::GstAudioManager>();
    gst->Play(taskid, audio_path, volume);
    gst->Pause(taskid);
    gst->Resume(taskid);
    gst->Cancel();
    gst = nullptr;
  }

  /// timer
  {
    TimerManager timer_manager;
    timer_manager.Start(
        []() {
          auto current = Timestamp::MonotonicMilliseconds();
          std::cout << "current time:" << current << std::endl;
        },
        -1, 1 * 1000);
  }

  /// thread poll
  {
    kviolet::ThreadPool thread_poll;
    thread_poll.Commit([]() { std::cout << "task" << std::endl; });
  }

  /// ringbuffer
  {}

  /// message queue
  {}

  /// grpc
  {}

  /// dbus
  {}

  return 0;
}
