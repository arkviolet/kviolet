

#include <kviolet/kviolet.h>
#include <kviolet_3rd/kviolet_3rd.h>

int main(int argc, char** argv) {
  (void)argc;
  (void)argv;

  int volume = 50;                                             // 0-100
  std::string audio_path = "~/workspace/sounds/test.wav";      // *.wav
  std::string gst_path = "file:///workspace/sounds/test.mp3";  // *.wav *.mp3

  std::string taskid = "123456";

  auto pulseaudio = std::make_shared<kviolet::PulseAudioManager>();
  auto gst = std::make_shared<kviolet::GstAudioManager>();

  gst->Play(taskid, audio_path, volume);
  pulseaudio->Play(taskid, audio_path, volume);

  gst = nullptr;
  pulseaudio = nullptr;

  return 0;
}
