

#include <kviolet/kviolet.h>
#include <kviolet_3rd/kviolet_3rd.h>

using namespace kviolet::timestamp;

int main(int argc, char** argv) {
  (void)argc;
  (void)argv;

  // 0-100
  int volume = 50;

  // *.wav
  std::string audio_path = "/home/user/workspace/sounds/test.wav";

  // *.wav *.mp3
  std::string gst_path = "file://home/user/workspace/sounds/test.mp3";

  auto taskid = std::to_string(Timestamp::MonotonicMilliseconds());

  auto pulseaudio = std::make_shared<kviolet::PulseAudioManager>();
  auto gst = std::make_shared<kviolet::GstAudioManager>();

  gst->Play(taskid, audio_path, volume);
  pulseaudio->Play(taskid, audio_path, volume);

  std::cout << "=== Pause ===" << std::endl;
  gst->Pause();
  gst->Pause(taskid);
  pulseaudio->Pause();
  pulseaudio->Pause(taskid);
  std::this_thread::sleep_for(std::chrono::seconds(2));

  std::cout << "=== Resume ===" << std::endl;
  pulseaudio->Resume();
  pulseaudio->Resume(taskid);
  gst->Resume();
  gst->Resume(taskid);
  std::this_thread::sleep_for(std::chrono::seconds(2));

  std::cout << "=== Cancel ===" << std::endl;
  pulseaudio->Cancel();
  pulseaudio->Cancel(taskid);
  gst->Cancel();
  gst->Cancel(taskid);
  std::this_thread::sleep_for(std::chrono::seconds(2));

  std::cout << "=== close ===" << std::endl;

  pulseaudio = nullptr;
  gst = nullptr;

  return 0;
}
