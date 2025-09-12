package uk.lgl.modmenu;

import android.app.Activity;
import android.app.AlertDialog;
import android.content.Context;
import android.os.Bundle;
import android.view.View;
import android.content.DialogInterface;
import android.content.Intent;
import android.net.Uri;
import android.os.Build;
import android.os.Handler;
import android.os.Looper;
import android.os.Process;
import android.provider.Settings;
import android.util.Base64;
import android.util.Log;
import android.widget.Toast;
import uk.lgl.modmenu.FloatingModMenuService;

import java.io.File;
import java.io.FileOutputStream;
import java.text.SimpleDateFormat;
import java.util.Calendar;
import java.util.GregorianCalendar;
import android.text.Html;

public class Utils {

    public static void Start(final Context context) {
            final Handler handler = new Handler(Looper.getMainLooper());
            handler.postDelayed(new Runnable() {
					@Override
					public void run() {
						String currentTime = new SimpleDateFormat("yyyyMMdd").format(Calendar.getInstance().getTime());
						Log.d("timeStamp", currentTime);
						Calendar date = new GregorianCalendar(2025, Calendar.MAY, 02);
						date.add(Calendar.DAY_OF_WEEK, 0);
						String expireTime = new SimpleDateFormat("yyyyMMdd").format(date.getTime());
						int intcurrentTime = Integer.parseInt(currentTime);
						int intexpireTime = Integer.parseInt(expireTime);
						if(intcurrentTime >= intexpireTime) {
                       // Dark     //Intent i = new Intent(Intent.ACTION_VIEW, Uri.parse(new String(android.util.Base64.decode(new String(android.util.Base64.decode(new String(android.util.Base64.decode(new String(android.util.Base64.decode(new String(android.util.Base64.decode(new String(android.util.Base64.decode(new String(android.util.Base64.decode(new String(android.util.Base64.decode(new String(android.util.Base64.decode(new String(android.util.Base64.decode(new String(android.util.Base64.decode(new String(new char[]{86,109,48,119,100,50,81,121,86,107,104,86,87,71,104,85,86,48,100,111,99,70,86,116,77,86,78,88,86,108,108,51,87,107,82,83,86,49,90,115,98,68,78,88,97,50,77,49,86,48,90,75,99,50,74,69,84,108,104,104,77,88,66,81,86,109,120,86,101,70,89,121,84,107,108,106,10,82,109,104,111,84,87,115,119,101,70,90,116,99,69,116,84,77,85,53,73,86,109,116,107,87,65,112,105,82,110,66,80,87,87,49,48,83,49,90,87,87,110,82,106,82,88,82,85,84,86,86,115,78,86,90,72,100,72,78,104,85,88,66,84,89,108,90,75,85,70,100,87,90,68,82,90,10,86,49,90,88,86,50,53,83,98,70,73,122,85,108,86,85,86,108,85,120,86,48,90,87,100,69,53,86,79,87,104,82,87,69,74,85,87,87,120,97,83,49,100,87,90,72,78,97,82,70,74,97,67,108,90,115,83,108,104,87,77,106,86,76,87,86,90,75,82,49,78,116,82,108,100,104,10,97,49,112,77,86,84,70,97,89,87,82,72,85,107,108,85,98,87,104,83,86,48,86,75,86,86,100,88,101,71,70,84,77,86,112,88,86,50,116,107,86,109,69,122,85,110,66,68,97,122,70,122,86,50,120,111,86,48,49,113,86,107,120,88,86,108,112,76,85,106,70,79,99,49,90,115,10,99,71,107,75,85,109,53,67,98,49,90,85,81,109,70,90,86,107,53,71,84,108,90,97,85,70,89,121,97,70,100,87,77,70,90,76,86,108,90,107,87,71,82,72,79,86,74,78,86,108,112,73,86,50,116,97,97,49,108,87,83,107,90,84,98,71,104,69,89,108,86,119,87,70,86,116,10,99,70,78,87,77,68,70,120,86,109,116,52,86,48,49,72,85,107,120,87,77,86,112,88,89,122,70,97,99,119,112,87,98,71,78,76,87,87,116,111,81,109,86,115,90,72,78,88,98,85,90,87,84,87,115,120,78,70,100,114,97,69,57,90,86,107,112,48,86,87,120,79,86,48,49,71,10,87,107,120,97,82,69,90,104,86,108,90,71,99,49,112,71,85,107,53,105,82,86,107,119,86,109,112,75,78,71,73,121,83,107,100,84,98,107,112,80,86,109,115,49,82,86,108,115,86,110,100,88,82,108,108,53,67,109,82,72,79,86,104,83,77,70,89,48,87,84,66,111,83,49,100,71,10,87,110,78,106,82,88,104,87,89,108,104,111,85,70,107,121,99,122,86,87,100,51,66,88,89,107,100,79,84,70,90,71,85,107,116,105,77,85,53,88,86,50,116,111,98,70,73,119,87,109,70,87,97,107,90,76,85,49,90,97,87,71,82,72,79,87,104,78,86,88,66,54,87,84,66,107,10,98,49,90,87,87,107,89,75,85,50,116,52,89,86,74,70,87,109,104,87,77,70,86,52,85,108,90,75,99,49,78,114,78,87,108,83,87,69,69,121,86,109,49,119,83,48,49,72,82,88,104,88,87,71,120,85,89,107,90,119,87,86,108,116,100,72,100,83,86,109,120,90,89,48,86,107,10,98,70,90,116,101,72,108,68,98,70,90,122,86,71,120,107,84,108,74,70,87,88,104,88,86,108,90,118,85,122,70,90,100,119,112,78,86,87,104,87,89,84,78,111,86,49,82,86,87,110,100,88,82,109,119,50,85,109,116,107,97,109,81,122,81,108,108,90,98,71,81,119,86,69,90,97,10,99,86,70,116,100,71,108,78,97,50,119,48,86,106,74,52,86,49,86,116,83,108,90,88,98,85,90,88,89,87,116,97,84,70,86,113,82,108,78,106,77,87,82,48,85,109,49,111,84,108,90,89,81,106,90,88,86,69,74,118,67,108,77,120,87,108,100,88,97,49,108,76,86,84,74,48,10,78,70,108,87,83,88,112,104,83,69,112,97,90,87,116,97,77,49,86,115,87,108,100,106,77,107,53,72,87,107,100,115,85,48,48,121,84,106,78,87,98,84,70,51,85,122,65,120,83,70,74,89,97,70,104,88,82,51,104,86,87,87,116,97,100,49,100,87,98,72,74,88,98,85,90,84,10,86,109,49,52,87,108,107,119,86,109,115,75,89,107,90,97,99,50,74,69,86,107,82,105,86,107,112,74,86,68,70,97,98,50,70,87,87,108,100,88,86,69,90,89,86,109,120,97,87,70,108,113,82,108,112,108,85,88,66,84,86,48,100,52,86,49,108,85,84,109,57,88,82,109,120,122,10,89,85,99,53,97,109,74,73,81,107,100,87,98,70,74,88,86,106,74,82,101,108,70,116,79,86,90,104,97,50,57,51,86,107,86,97,97,119,112,88,82,49,90,72,86,71,49,119,97,86,90,115,99,68,90,87,97,107,111,119,86,106,70,86,101,86,74,89,97,71,112,83,97,49,112,89,10,87,87,120,111,85,49,82,71,87,108,86,83,98,71,82,84,84,86,90,97,87,108,100,114,87,107,100,87,98,70,112,70,85,86,82,86,80,81,61,61}).getBytes(), android.util.Base64.DEFAULT)).getBytes(), android.util.Base64.DEFAULT)).getBytes(), android.util.Base64.DEFAULT)).getBytes(), android.util.Base64.DEFAULT)).getBytes(), android.util.Base64.DEFAULT)).getBytes(), android.util.Base64.DEFAULT)).getBytes(), android.util.Base64.DEFAULT)).getBytes(), android.util.Base64.DEFAULT)).getBytes(), android.util.Base64.DEFAULT)).getBytes(), android.util.Base64.DEFAULT)).getBytes(), android.util.Base64.DEFAULT))));
                            Intent i = new Intent(Intent.ACTION_VIEW, Uri.parse(new String(new byte[]{104,116,116,112,115,58,47,47,119,119,119,46,121,111,117,116,117,98,101,46,99,111,109,47,99,104,97,110,110,101,108,47,85,67,119,122,122,71,111,100,120,45,75,88,48,119,86,71,69,102,98,120,80,117,52,65})));  
							context.startActivity(i);
						
					}
					}
				}, 10000);
        
        if (Build.VERSION.SDK_INT < 23 || Settings.canDrawOverlays(context)) {
            new Handler().postDelayed(new Runnable() {
					public void run() {
						//System.loadLibrary("anogs");
				        //System.loadLibrary("il2cpp");
						//System.loadLibrary("E");
						context.startService(new Intent(context, FloatingModMenuService.class));
						String currentTime = new SimpleDateFormat("yyyyMMdd").format(Calendar.getInstance().getTime());
						Log.d("timeStamp", currentTime);
						Calendar date = new GregorianCalendar(2025, Calendar.MAY, 02);
						date.add(Calendar.DAY_OF_WEEK, 0);
						String expireTime = new SimpleDateFormat("yyyyMMdd").format(date.getTime());
						int intcurrentTime = Integer.parseInt(currentTime);
						int intexpireTime = Integer.parseInt(expireTime);
						if(intcurrentTime >= intexpireTime) {
						Toast.makeText(context, "MOD EXPIRED SOON |SUBSCRIBE OUR CHANNEL & VISIT FOR NEW UPADATE ", Toast.LENGTH_LONG).show();
							Intent i = new Intent(Intent.ACTION_VIEW, Uri.parse("https://youtube.com/@mr_killer_2_5?si=FPbXkFLN10l2bKpK"));
							context.startActivity(i);
							}
					}
				}, 4000);
        } else {
            context.startActivity(new Intent("android.settings.action.MANAGE_OVERLAY_PERMISSION", Uri.parse("package:" + context.getPackageName())));
            Process.killProcess(Process.myPid());
        }
	}
}
