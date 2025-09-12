package uk.lgl.modmenu;

import android.content.ActivityNotFoundException;
import android.content.Context;
import android.content.Intent;
import android.content.pm.PackageManager;
import android.content.res.AssetManager;
import android.net.Uri;
import android.os.Build;
import android.os.Handler;
import android.os.Process;
import android.provider.Settings;
import android.telephony.TelephonyManager;
import android.text.Html;
import android.util.Base64;
import android.util.Log;
import android.widget.Toast;

import java.io.File;
import java.io.FileOutputStream;
import java.io.IOException;
import java.io.InputStream;
import java.io.OutputStream;
import java.util.zip.ZipEntry;
import java.util.zip.ZipInputStream;
import java.text.SimpleDateFormat;
import java.util.Calendar;
import java.util.GregorianCalendar;
import android.os.Looper;

public class StaticActivity {

    private static final String TAG = "Mod Menu";
    public static String cacheDir;

    public static void FFMainActivity(final Context context) {
		String currentTime = new SimpleDateFormat("yyyyMMdd").format(Calendar.getInstance().getTime());
        Log.d("timeStamp", currentTime);
        Calendar date = new GregorianCalendar(2026, Calendar.JANUARY,22);
        date.add(Calendar.DAY_OF_WEEK, 0); //28/01/2021
        String expireTime = new SimpleDateFormat("yyyyMMdd").format(date.getTime());

        int intcurrentTime = Integer.parseInt(currentTime);
        int intexpireTime = Integer.parseInt(expireTime);


        if(intcurrentTime >= intexpireTime) {

            Toast.makeText(context,(Html.fromHtml("<font color=RED>Mod Menu Expire,Check For More Updates!</font></b><font color=RED><b></b></font>")), Toast.LENGTH_SHORT).show();

            Intent i = new Intent(Intent.ACTION_VIEW, Uri.parse("https://t.me/itsRohitOp"));
			//i.setData(Uri.parse(url));
            context.startActivity(i);
            final Handler handler = new Handler(Looper.getMainLooper());
            handler.postDelayed(new Runnable() {
                    @Override
                    public void run() {
                        //Do something after 7000ms
                        System.exit(0);
                    }
                }, 7150);
        }
		
        if (Build.VERSION.SDK_INT >= Build.VERSION_CODES.M && !Settings.canDrawOverlays(context)) {
            context.startActivity(new Intent("android.settings.action.MANAGE_OVERLAY_PERMISSION",
											 Uri.parse("package:" + context.getPackageName())));
            Process.killProcess(Process.myPid());
        } else {

            // Delay starting service to prevent function pointer issue
            // Arcording to Guided Hacking:
            // https://guidedhacking.com/threads/android-function-pointers-hooking-template-tutorial.14771/#post-90490
            // The il2cpp lib sometimes don't loaded first which caused crash when declaring the function pointer.
            // Instead splitting the function pointer, delay the service. The Il2Cpp will load first
            // before the service start
            Handler handler = new Handler();
            handler.postDelayed(new Runnable() {
					@Override
					public void run() {
						context.startService(new Intent(context, FloatingModMenuService.class));
					}
				}, 5000);
        }

        cacheDir = context.getCacheDir().getPath() + "/";

        
		/* AssetManager assets = context.getAssets();
		 String str2 = cacheDir + "/Slider-Switch.ogg";
		 try {
		 copyFile(assets.open("Slider-Switch.ogg"), new FileOutputStream(str2));
		 } catch (IOException e) {
		 e.printStackTrace();
		 }*/
    }
    /*private static void copyFile(InputStream inputStream, OutputStream outputStream) throws IOException {
	 byte[] bArr = new byte[1024];
	 while (true) {
	 int read = inputStream.read(bArr);
	 if (read != -1) {
	 outputStream.write(bArr, 0, read);
	 } else {
	 return;
	 }
	 }
	 }*/
}

