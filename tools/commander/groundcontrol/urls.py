from django.conf.urls import url
from django.contrib import admin

from . import views

admin.autodiscover()

urlpatterns = [url(r'^$', views.index, name='index'),  # Routing in url like [127.0.0.1:8000/abc]
               url(r'^(\w+)/(\w+)/(\w+)/$', views.router, name ='router_3_layers'),  # Routing in url like [127.0.0.1:8000/abc/def]
               url(r'^(\w+)/(\w+)/$', views.router, name ='router_2_layer'),  # Routing in url like [127.0.0.1:8000/abc/def/ghi]
               url(r'^(\w+)/$', views.router, name ='router_1_layer'),  # Routing in url like [127.0.0.1:8000/abc/def/ghi/jkl]
               url(r'^(\w+).pug$', views.router, name='router_1_layer'),
               url(r'^(\w+)/(\w+)/(\w+).pug$', views.router, name ='router_3_layers'),  # Routing in url like [127.0.0.1:8000/abc/def]
               url(r'^(\w+)/(\w+).pug$', views.router, name ='router_2_layer'),  # Routing in url like [127.0.0.1:8000/abc/def/ghi]

               ]