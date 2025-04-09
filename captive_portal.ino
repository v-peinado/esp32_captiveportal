#include <WiFi.h>
#include <DNSServer.h>
#include <WebServer.h>
#include <map>
#include <string>

/* Access Point Configuration */
const char      *g_ssid = "Free_WiFi";
const IPAddress g_ap_ip(192, 168, 4, 1);
const int       g_web_port = 80;
const char      *g_admin_pwd = "admin123";
const byte      g_dns_port = 53;

/* Global variables for Statistics */
int             g_visitors = 0;
int             g_tests_completed = 0;

/* Store IPs that have already visited */
std::map<String, bool> g_visitor_ips;

/* Web server and DNS server instances */
DNSServer       g_dns_server;
WebServer       g_web_server(g_web_port);

void setup(void)
{
    Serial.begin(115200);
    delay(1000);
    WiFi.mode(WIFI_AP);
    WiFi.softAPConfig(g_ap_ip, g_ap_ip, IPAddress(255, 255, 255, 0));
    WiFi.softAP(g_ssid);
    g_dns_server.start(g_dns_port, "*", g_ap_ip);
    g_web_server.on("/", handle_root);
    g_web_server.on("/info", handle_info);
    g_web_server.on("/completed", handle_completed);
    g_web_server.on("/reset", handle_reset_form);
    g_web_server.on("/perform_reset", HTTP_POST, handle_perform_reset);
    g_web_server.onNotFound(handle_root);
    g_web_server.begin();
}

void loop(void)
{
    g_dns_server.processNextRequest();
    g_web_server.handleClient();
}

void handle_root(void)
{
    g_web_server.sendHeader("Location", "/info", true);
    g_web_server.send(302, "text/plain", "");
}

void handle_info(void)
{
    String client_ip;
    String html;
    
    // Get client IP address
    client_ip = g_web_server.client().remoteIP().toString();
    
    // Count unique visitors based on IP
    if (g_visitor_ips.find(client_ip) == g_visitor_ips.end()) {
        g_visitor_ips[client_ip] = true;
        g_visitors++;
    }
    
    html = "<!DOCTYPE html><html><head><title>WiFi Security Alert</title>";
    html += "<meta name='viewport' content='width=device-width, initial-scale=1.0'>";
    html += "<style>body{font-family:Arial,sans-serif;margin:0;padding:0;";
    html += "color:#333;background-color:#f5f5f5;}";
    html += "h1{color:#cc0000;text-align:center;margin:15px 0;font-size:24px;}";
    html += ".container{max-width:600px;margin:0 auto;background-color:white;";
    html += "padding:20px;box-shadow:0 2px 10px rgba(0,0,0,0.1);}";
    html += ".data-item{background-color:#ffebee;border-left:4px solid #cc0000;";
    html += "padding:10px;margin-bottom:8px;}";
    html += ".counters{background-color:#f0f0f0;padding:10px;margin:15px 0;";
    html += "border-radius:4px;text-align:center;}";
    html += ".counter-box{display:inline-block;width:45%;text-align:center;}";
    html += ".counter-value{font-size:24px;font-weight:bold;color:#cc0000;}";
    html += ".counter-label{font-size:12px;color:#666;}";
    html += ".button{background-color:#4CAF50;border:none;color:white;";
    html += "padding:10px 15px;text-align:center;text-decoration:none;";
    html += "display:inline-block;font-size:16px;margin:10px 2px;";
    html += "cursor:pointer;border-radius:4px;}</style></head>";
    html += "<body><div class='container'>";
    html += "<h1>⚠️ WARNING: Unsecured WiFi Network ⚠️</h1>";
    html += "<div class='counters'><div class='counter-box'>";
    html += "<div class='counter-value'>" + String(g_visitors) + "</div>";
    html += "<div class='counter-label'>Visitors</div></div>";
    html += "<div class='counter-box'>";
    html += "<div class='counter-value'>" + String(g_tests_completed) + "</div>";
    html += "<div class='counter-label'>Tests Completed</div></div></div>";
    html += "<p><strong>This network could be stealing:</strong></p>";
    html += "<div class='data-item'>📱 Your email and social media passwords</div>";
    html += "<div class='data-item'>💳 Your credit card information</div>";
    html += "<div class='data-item'>🔑 Your login credentials for websites</div>";
    html += "<div class='data-item'>📋 Your browsing history</div>";
    html += "<div class='data-item'>📝 Your private messages and emails</div>";
    html += "<div class='data-item'>📍 Your current location</div>";
    html += "<p><strong>Security Tips:</strong></p><ul>";
    html += "<li>Avoid connecting to open WiFi networks without passwords</li>";
    html += "<li>Always verify that websites use HTTPS (padlock icon)</li>";
    html += "<li>Never enter sensitive data while using public WiFi</li>";
    html += "<li>Use a VPN when connected to public networks</li></ul>";
    html += "<div style='text-align:center;margin-top:20px;'>";
    html += "<a href='/completed' class='button'>I understand the risks</a>";
    html += "</div>";
    html += "<p style='font-size:14px;color:#666;text-align:center;";
    html += "margin-top:30px;'>Cybersecurity Educational Project - ESP32</p>";
    html += "<div style='text-align:center;margin-top:20px;font-size:12px;'>";
    html += "<a href='/reset' style='color:#999;'>";
    html += "Reset counters (administrators only)</a></div></div></body></html>";
    g_web_server.send(200, "text/html", html);
}

void handle_completed(void)
{
    String html;
    g_tests_completed++;
    html = "<!DOCTYPE html><html><head><title>Test Completed!</title>";
    html += "<meta name='viewport' content='width=device-width, initial-scale=1.0'>";
    html += "<style>body{font-family:Arial,sans-serif;margin:0;padding:0;";
    html += "color:#333;background-color:#f5f5f5;}";
    html += "h1{color:#4CAF50;text-align:center;margin:15px 0;font-size:24px;}";
    html += ".container{max-width:600px;margin:0 auto;background-color:white;";
    html += "padding:20px;box-shadow:0 2px 10px rgba(0,0,0,0.1);}";
    html += ".success-box{background-color:#e8f5e9;border-left:4px solid ";
    html += "#4CAF50;padding:15px;margin:15px 0;}";
    html += ".button{background-color:#4CAF50;border:none;color:white;";
    html += "padding:10px 15px;text-align:center;text-decoration:none;";
    html += "display:inline-block;font-size:16px;margin:10px 2px;";
    html += "cursor:pointer;border-radius:4px;}</style></head>";
    html += "<body><div class='container'>";
    html += "<h1>✅ Thank you for participating! ✅</h1>";
    html += "<div class='success-box'>";
    html += "<p><strong>You have completed the WiFi security awareness test.</strong></p>";
    html += "<p>Always remember to verify the security of a network before ";
    html += "connecting and use additional protection measures like VPNs ";
    html += "when using public networks.</p></div>";
    html += "<div style='text-align:center;margin-top:20px;'>";
    html += "<a href='/info' class='button'>Return to information</a></div>";
    html += "<p style='font-size:14px;color:#666;text-align:center;";
    html += "margin-top:30px;'>Cybersecurity Educational Project - ESP32</p>";
    html += "</div></body></html>";
    g_web_server.send(200, "text/html", html);
}

void handle_reset_form(void)
{
    String html;
    html = "<!DOCTYPE html><html><head><title>Administrator Access</title>";
    html += "<meta name='viewport' content='width=device-width, initial-scale=1.0'>";
    html += "<style>body{font-family:Arial,sans-serif;margin:0;padding:0;";
    html += "color:#333;background-color:#f5f5f5;}";
    html += "h1{color:#333;text-align:center;margin:15px 0;font-size:24px;}";
    html += ".container{max-width:600px;margin:50px auto;background-color:white;";
    html += "padding:20px;box-shadow:0 2px 10px rgba(0,0,0,0.1);}";
    html += "form{margin-top:20px;}label{display:block;margin-bottom:5px;}";
    html += "input[type=password]{width:100%;padding:8px;margin-bottom:20px;";
    html += "box-sizing:border-box;}";
    html += "input[type=submit]{background-color:#4CAF50;border:none;";
    html += "color:white;padding:10px 15px;cursor:pointer;}";
    html += ".back-link{display:block;text-align:center;margin-top:20px;";
    html += "color:#666;text-decoration:none;}</style></head>";
    html += "<body><div class='container'>";
    html += "<h1>Administrator Access</h1>";
    html += "<p>Enter the administrator password to reset the counters:</p>";
    html += "<form action='/perform_reset' method='post'>";
    html += "<label for='password'>Password:</label>";
    html += "<input type='password' id='password' name='password' required>";
    html += "<input type='submit' value='Reset Counters'></form>";
    html += "<a href='/info' class='back-link'>Return to information</a>";
    html += "</div></body></html>";
    g_web_server.send(200, "text/html", html);
}

void handle_perform_reset(void)
{
    String input_password;
    String html;
    input_password = g_web_server.arg("password");
    if (input_password == g_admin_pwd)
    {
        g_visitors = 0;
        g_tests_completed = 0;
        g_visitor_ips.clear();
        html = "<!DOCTYPE html><html><head><title>Counters Reset</title>";
        html += "<meta name='viewport' content='width=device-width, initial-scale=1.0'>";
        html += "<meta http-equiv='refresh' content='2;url=/info'>";
        html += "<style>body{font-family:Arial,sans-serif;margin:0;padding:0;";
        html += "color:#333;background-color:#f5f5f5;}";
        html += ".container{max-width:600px;margin:50px auto;background-color:";
        html += "white;padding:20px;box-shadow:0 2px 10px rgba(0,0,0,0.1);";
        html += "text-align:center;}";
        html += ".success{color:#4CAF50;}</style></head>";
        html += "<body><div class='container'>";
        html += "<h2 class='success'>Counters successfully reset</h2>";
        html += "<p>Redirecting to main page...</p></div></body></html>";
    }
    else
    {
        html = "<!DOCTYPE html><html><head><title>Access Denied</title>";
        html += "<meta name='viewport' content='width=device-width, initial-scale=1.0'>";
        html += "<style>body{font-family:Arial,sans-serif;margin:0;padding:0;";
        html += "color:#333;background-color:#f5f5f5;}";
        html += ".container{max-width:600px;margin:50px auto;background-color:";
        html += "white;padding:20px;box-shadow:0 2px 10px rgba(0,0,0,0.1);";
        html += "text-align:center;}";
        html += ".error{color:#cc0000;}";
        html += ".button{background-color:#4CAF50;border:none;color:white;";
        html += "padding:10px 15px;text-align:center;text-decoration:none;";
        html += "display:inline-block;margin-top:20px;}</style></head>";
        html += "<body><div class='container'>";
        html += "<h2 class='error'>Access Denied</h2>";
        html += "<p>The password you entered is incorrect.</p>";
        html += "<a href='/reset' class='button'>Try Again</a>";
        html += "</div></body></html>";
    }
    g_web_server.send(200, "text/html", html);
}