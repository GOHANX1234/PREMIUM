package uk.lgl.modmenu;

import android.content.Context; 
import android.content.res.Resources; 
import android.graphics.Bitmap; 
import android.graphics.BitmapFactory; 
import android.graphics.Color; 
import android.graphics.drawable.BitmapDrawable; 
import android.graphics.drawable.Drawable; 
import android.graphics.drawable.GradientDrawable; 
import android.graphics.drawable.StateListDrawable; 
import android.util.Base64; 
import android.util.DisplayMetrics; 
import android.util.TypedValue; 

public class Preferences {
    public static native void lllllllllllllllll(int id);

    public static native String YUMODZXD();

    public static native String YUYUYUYU()

    public static GradientDrawable bbbbb_aaaaaaaa(Context context) {
        GradientDrawable gradientDrawable = new GradientDrawable();
        gradientDrawable.setShape(0);
        gradientDrawable.setStroke(3, Color.parseColor("#00FF00")); // Green border
        gradientDrawable.setColor(Color.TRANSPARENT); // Transparent background instead of red
        gradientDrawable.setCornerRadii(new float[] { 20, 20, 10, 10, 20, 20, 10, 10 });
                gradientDrawable.setCornerRadius(TypedValue.applyDimension((int)1, (float)5.0f, (DisplayMetrics)context.getResources().getDisplayMetrics()));
        return gradientDrawable;
    }

    public static StateListDrawable bbbbb_hhhhh(Context context) {
        StateListDrawable stateListDrawable = new StateListDrawable();
        stateListDrawable.addState(new int[]{16842919}, (Drawable)Preferences.bbbbb_aaaaaaaa(context));
        stateListDrawable.addState(new int[]{16842908}, (Drawable)Preferences.bbbbb_aaaaaaaa(context));
        stateListDrawable.addState(new int[]{-16842908, -16842919}, (Drawable)Preferences.botoes(context));
        return stateListDrawable;
    }

    public static GradientDrawable botoes(Context context) {
        GradientDrawable gradientDrawable = new GradientDrawable();
        gradientDrawable.setShape(0);
        gradientDrawable.setStroke(3, Color.BLACK);
        gradientDrawable.setCornerRadius(0);
        gradientDrawable.setCornerRadius(TypedValue.applyDimension((int)1, (float)5.0f, (DisplayMetrics)context.getResources().getDisplayMetrics()));
        return gradientDrawable;
    }

    public static Drawable yu_icon(Context context, String string2) {
        byte[] arrby = Base64.decode((String)string2, (int)0);
        Bitmap bitmap = BitmapFactory.decodeByteArray((byte[])arrby, (int)0, (int)arrby.length);
        return new BitmapDrawable(context.getResources(), bitmap);
    }
}
