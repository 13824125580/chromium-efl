#ifndef CONTER_RENDERER_CLIENT_EFL_H
#define CONTER_RENDERER_CLIENT_EFL_H

#include "content/public/renderer/content_renderer_client.h"
#include "v8/include/v8.h"
#include "renderer/render_process_observer_efl.h"
#include "public/ewk_ipc_message.h"

namespace content {
class RenderView;
class RenderFrame;
class DocumentState;
}

class WrtWidget;

class ContentRendererClientEfl : public content::ContentRendererClient
{
 public:
  ContentRendererClientEfl();
  ~ContentRendererClientEfl();

  virtual void RenderThreadStarted();

  virtual void RenderViewCreated(content::RenderView* render_view);

  void SetWidgetInfo(int widgetHandle,
                     double scaleFactor,
                     const std::string &encodedBundle,
                     const std::string &theme);

  void WrtMessageReceived(const Ewk_IPC_Wrt_Message_Data& data);

  virtual void DidCreateScriptContext(blink::WebFrame* frame,
                                      v8::Handle<v8::Context> context,
                                      int extension_group,
                                      int world_id);

  virtual void WillReleaseScriptContext(blink::WebFrame* frame,
                                        v8::Handle<v8::Context>,
                                        int world_id);

  bool HandleNavigation(content::RenderFrame* render_frame,
                        content::DocumentState* document_state,
                        int opener_id,
                        blink::WebFrame* frame,
                        const blink::WebURLRequest& request,
                        blink::WebNavigationType type,
                        blink::WebNavigationPolicy default_policy,
                        bool is_redirect) OVERRIDE;

  virtual bool WillSendRequest(blink::WebFrame* frame,
                               content::PageTransition transition_type,
                               const GURL& url,
                               const GURL& first_party_for_cookies,
                               GURL* new_url);

 private:
  scoped_ptr<WrtWidget> wrt_widget_;
  scoped_ptr<RenderProcessObserverEfl> render_process_observer_;
};

#endif
