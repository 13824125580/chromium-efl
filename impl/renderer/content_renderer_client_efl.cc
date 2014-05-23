
#include <memory>

#include "url/gurl.h"
#include "content/public/renderer/render_thread.h"
#include "content/public/renderer/render_view.h"
#include "content/child/request_extra_data.h"
#include "renderer/render_view_observer_efl.h"
#include "content/public/renderer/content_renderer_client.h"
#include "third_party/WebKit/public/platform/WebURLRequest.h"
#include "third_party/WebKit/public/web/WebDataSource.h"
#include "third_party/WebKit/public/web/WebDocument.h"
#include "third_party/WebKit/public/web/WebFrame.h"
#include "third_party/WebKit/public/web/WebView.h"

#include "components/editing/content/renderer/editorclient_agent.h"
#include "renderer/content_renderer_client_efl.h"
#include "navigation_policy_params.h"
#include "wrt/wrtwidget.h"

ContentRendererClientEfl::ContentRendererClientEfl() {
  wrt_widget_.reset(new WrtWidget);
}

ContentRendererClientEfl::~ContentRendererClientEfl() {
}

void ContentRendererClientEfl::RenderThreadStarted()
{
  render_process_observer_.reset(new RenderProcessObserverEfl(this));
  content::RenderThread* thread = content::RenderThread::Get();
  thread->AddObserver(render_process_observer_.get());
}

void ContentRendererClientEfl::RenderViewCreated(content::RenderView* render_view) {
  // Deletes itself when render_view is destroyed.
  new RenderViewObserverEfl(render_view);
  new editing::EditorClientAgent(render_view);
}

bool ContentRendererClientEfl::HandleNavigation(content::RenderFrame* render_frame,
                                                content::DocumentState* document_state,
                                                int opener_id,
                                                blink::WebFrame* frame,
                                                const blink::WebURLRequest& request,
                                                blink::WebNavigationType type,
                                                blink::WebNavigationPolicy default_policy,
                                                bool is_redirect) {
  const content::RenderView* render_view =
      content::RenderView::FromWebView(frame->view());
  bool result = false;
  GURL referrer_url(GURL(request.httpHeaderField(blink::WebString::fromUTF8("Referer"))));
  blink::WebReferrerPolicy referrer_policy =  
      request.isNull() ? frame->document().referrerPolicy() : request.referrerPolicy();
  int render_view_id = render_view->GetRoutingID();

  NavigationPolicyParams params;
  params.render_view_id = render_view_id;
  params.url = request.url();
  params.referrer = content::Referrer(referrer_url, referrer_policy);
  params.policy = default_policy;
  params.is_main_frame = (frame->view()->mainFrame() == frame);
  params.type = type;
  params.is_redirect = is_redirect;

  blink::WebDataSource* ds = frame->provisionalDataSource();
  params.should_replace_current_entry = (ds ? ds->replacesCurrentHistoryItem() : false);

  // Sync message, renderer is blocked here.
  content::RenderThread::Get()->Send(new EwkHostMsg_DecideNavigationPolicy(
      params, &result));

  return result;
}

bool ContentRendererClientEfl::WillSendRequest(blink::WebFrame* frame,
                                               content::PageTransition transition_type,
                                               const GURL& url,
                                               const GURL& first_party_for_cookies,
                                               GURL* new_url) {
  wrt_widget_->ParseUrl(url, *new_url);
  return true;
}

void ContentRendererClientEfl::SetWidgetInfo(int widgetHandle,
                                             double scaleFactor,
                                             const std::string &encodedBundle,
                                             const std::string &theme) {
  wrt_widget_->SetWidgetInfo(widgetHandle, scaleFactor, encodedBundle, theme);
}

void ContentRendererClientEfl::WrtMessageReceived(const Ewk_IPC_Wrt_Message_Data& data) {
  wrt_widget_->messageReceived(data);
}

void ContentRendererClientEfl::DidCreateScriptContext(blink::WebFrame* frame,
                                                      v8::Handle<v8::Context> context,
                                                      int extension_group,
                                                      int world_id) {
  const content::RenderView* render_view = content::RenderView::FromWebView(frame->view());

  wrt_widget_->StartSession(context, render_view->GetRoutingID());
}

void ContentRendererClientEfl::WillReleaseScriptContext(blink::WebFrame* frame,
                                                        v8::Handle<v8::Context> context,
                                                        int world_id) {
  wrt_widget_->StopSession(context);
}
