package uk.lgl.modmenu;

import android.app.Activity;
import android.os.Bundle;
import android.text.format.Time;
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
import android.app.Activity;
import android.app.AlertDialog;
import android.os.Looper;
import android.os.Bundle;
import android.view.View;
import android.content.DialogInterface;
import java.text.SimpleDateFormat;
import java.util.Calendar;
import java.util.GregorianCalendar;
import uk.lgl.modmenu.R;
import android.content.pm.ActivityInfo;
import android.widget.ThemedSpinnerAdapter;
public class MainActivity extends Activity {
	public static final String APPLICATION_ID = "uk.lgl.modmenu";
    public static final String BUILD_TYPE = "debug";
    public static final boolean DEBUG = Boolean.parseBoolean("true");
    public static final int VERSION_CODE = 1;
    public static final String VERSION_NAME = "1.0";
	
	private static final String TAG = "Mod Menu";
    public static String FFMainActivity;
    public static String cacheDir;
    public String GameActivity = "com.dts.freefireth";
    public boolean hasLaunched = false;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
		StaticActivity.FFMainActivity(this);
        
        Thread.setDefaultUncaughtExceptionHandler(
            new Thread.UncaughtExceptionHandler() {
                @Override
                public void uncaughtException(Thread thread, Throwable e) {
                    Log.e("AppCrash", "Error just lunched ");
                    Log.e("Mod_menu", "Error. Game's main activity does not exist");
                }
            });
        if (!hasLaunched) {
            try {
                hasLaunched = true;
                MainActivity.this.startActivity(new Intent(MainActivity.this, Class.forName(MainActivity.this.GameActivity)));
            } catch (ClassNotFoundException e) {
                e.printStackTrace();
                Toast.makeText(MainActivity.this, "Error just lunched ", Toast.LENGTH_LONG).show();
                Toast.makeText(MainActivity.this, "Error. Game's main activity does not exist", Toast.LENGTH_LONG).show();
                return;
            }
        }
    }
}
