package uk.lgl.modmenu;

import android.annotation.TargetApi;
import android.app.ActivityManager;
import android.app.ActivityManager.RunningAppProcessInfo;
import android.app.AlertDialog;
import android.app.Service;
import android.content.Context;
import android.content.Intent;
import android.content.res.ColorStateList;
import android.graphics.BitmapFactory;
import android.graphics.Canvas;
import android.graphics.Color;
import android.graphics.Paint;
import android.graphics.drawable.GradientDrawable;
import android.graphics.PixelFormat;
import android.graphics.Bitmap;
import android.graphics.PorterDuff;
import android.graphics.Typeface;
import android.media.MediaPlayer;
import android.net.Uri;
import android.os.Build;
import android.os.Handler;
import android.os.IBinder;
import android.graphics.drawable.Drawable;
import android.text.Html;
import android.text.InputFilter;
import android.text.InputType;
import android.text.method.DigitsKeyListener;
import android.util.Base64;
import android.util.Log;
import android.util.TypedValue;
import android.view.Gravity;
import android.view.MotionEvent;
import android.view.View;
import android.view.ViewGroup;
import android.view.WindowManager;
import android.view.inputmethod.InputMethodManager;
import android.webkit.WebSettings;
import android.webkit.WebView;
import android.widget.AdapterView;
import android.widget.ArrayAdapter;
import android.widget.Button;
import android.widget.CompoundButton;
import android.widget.EditText;
import android.widget.FrameLayout;
import android.widget.ImageView;
import android.widget.LinearLayout;
import android.widget.RelativeLayout;
import android.widget.ScrollView;
import android.widget.SeekBar;
import android.widget.Spinner;
import android.widget.Switch;
import android.widget.TextView;
import android.widget.Toast;
import uk.lgl.modmenu.ESPView;
import uk.lgl.modmenu.Utils;
import java.io.File;
import java.util.Arrays;
import java.util.LinkedList;
import java.util.List;
import java.util.Objects;
import static android.view.ViewGroup.LayoutParams.MATCH_PARENT;
import android.content.res.ColorStateList;
import android.content.res.AssetManager;
import java.io.IOException;
import android.content.DialogInterface;

import android.graphics.drawable.ColorDrawable;
import android.graphics.drawable.GradientDrawable;
import android.graphics.PixelFormat;
import android.graphics.PorterDuff;
import android.graphics.Typeface;
import android.media.MediaPlayer;
import android.widget.ProgressBar;
import android.os.Looper;

import android.graphics.drawable.BitmapDrawable;
import static uk.lgl.modmenu.StaticActivity.cacheDir;
import android.net.ConnectivityManager;
import java.net.HttpURLConnection;
import java.io.BufferedReader;
import java.io.InputStream;
import java.net.URL;
import android.os.AsyncTask;
import android.annotation.SuppressLint;
import java.io.InputStreamReader;
import android.widget.LinearLayout.LayoutParams;
import android.widget.CheckBox;
import android.widget.RadioButton;
import android.widget.RadioGroup;
import android.util.DisplayMetrics;
import android.transition.Visibility;
import java.util.Calendar;
import android.animation.ArgbEvaluator;
import android.animation.ValueAnimator;
import android.animation.TimeAnimator;
import android.graphics.drawable.RippleDrawable;
import static android.view.ViewGroup.LayoutParams.WRAP_CONTENT;
import static android.view.ViewGroup.LayoutParams.MATCH_PARENT;
import static android.widget.RelativeLayout.ALIGN_PARENT_LEFT;
import static android.widget.RelativeLayout.ALIGN_PARENT_RIGHT;
public class FloatingModMenuService extends Service {
        // ImGui Style Colors
    final int TEXT_COLOR = Color.parseColor("#FFFFFF");
    final int TEXT_COLOR_2 = Color.parseColor("#B3B3B3");
    final int IMGUI_ACCENT = Color.parseColor("#1E90FF");
    final int IMGUI_BG_DARK = Color.parseColor("#1E1E1E");
    final int IMGUI_BG_DARKER = Color.parseColor("#161616");
    final int IMGUI_BORDER = Color.parseColor("#3A3A3A");
    final int BTN_COLOR = Color.parseColor("#2D2D2D");
    final int MENU_BG_COLOR = Color.parseColor("#E8161616"); //#AARRGGBB
    final int MENU_FEATURE_BG_COLOR = Color.parseColor("#FF1E1E1E"); //#AARRGGBB
    final int MENU_WIDTH = 320;
    final int MENU_HEIGHT = 400;
    final float MENU_CORNER = 20f;
    final int ICON_SIZE = 50;
    final float ICON_ALPHA = 0.5f; //Transparent
    private MediaPlayer FXPlayer;
    public View mFloatingView;
    private Button close;
    private Button kill;
    private LinearLayout mButtonPanel;
    public RelativeLayout mCollapsed;
    public LinearLayout mExpanded;
    private RelativeLayout mRootContainer;
    public WindowManager mWindowManager;
    public WindowManager.LayoutParams params;
    private LinearLayout patches;
        private LinearLayout patches2;
    // Tab system variables
    private LinearLayout tabContainer;
    private LinearLayout tabContent;
    private Button aimTab, espTab, brutalTab, otherTab;
    private LinearLayout aimContent, espContent, brutalContent, otherContent;
    private int currentTab = 0; // 0=AIM, 1=ESP, 2=BRUTAL, 3=OTHER
    private FrameLayout rootFrame;
    private ImageView startimage;
    private Button toggleBtn;
    private LinearLayout imguiBar;
        private Drawable imagem;
        private Drawable logo;
    private LinearLayout view1;
    private LinearLayout view2;
        private GradientDrawable thumb;

        //Canvas 
        private ESPView overlayView;
        public static native void DrawOn(ESPView espView, Canvas canvas);
        private WindowManager.LayoutParams espParams;
    private native String ForegroundGravity();
    private native String Gravity();
    private AlertDialog alert;
    private EditText edittextvalue;
    private ImageView BadLogo2;
    private static final String TAG = "Mod Menu";

    private LinearLayout.LayoutParams hr;

    //initialize methods from the native library
    public static native String Toast();

    private  GradientDrawable gd = new GradientDrawable();
        private  ValueAnimator animator;
        private  ValueAnimator animator_c;

    public native void Changes(int feature, int value);

    private native String[] getFeatureList();



    @Override
    public IBinder onBind(Intent intent) {
        return null;
    }

    //Override our Start Command so the Service doesnt try to recreate itself when the App is closed
    public int onStartCommand(Intent intent, int i, int i2) {
        return Service.START_NOT_STICKY;
    }

    private int getLayoutType() {
        if (Build.VERSION.SDK_INT >= 26) {
            return 2038;
        }
        if (Build.VERSION.SDK_INT >= 24) {
            return 2002;
        }
        if (Build.VERSION.SDK_INT >= 23) {
            return 2005;
        }
        return 2003;
    }

        private void DrawCanvas() {
        WindowManager.LayoutParams layoutParams;
        this.espParams = layoutParams = new WindowManager.LayoutParams(-1, -1, this.getLayoutType(), 56, -3);
        layoutParams.gravity = 8388659;
        this.espParams.x = 0;
        this.espParams.y = 0;
        this.mWindowManager.addView((View)this.overlayView, (ViewGroup.LayoutParams)this.espParams);
    }

    //When this Class is called the code in this function will be executed
    @Override
    public void onCreate() {
        super.onCreate();
        System.loadLibrary("MRKILLER2.5");
                this.overlayView = new ESPView((Context)this);
        initFloating();
        //CreateMenuList();
                DrawCanvas();
                //l  initAlertDiag();

                /*
                 final Handler handler = new Handler();
                 handler.post(new Runnable() {
                 public void run() {
                 handler.postDelayed(this, 1000);*/
    }

    private void initFloating() {
        rootFrame = new FrameLayout(getBaseContext()); // Global markup
        mRootContainer = new RelativeLayout(getBaseContext()); // Markup on which two markups of the icon and the menu itself will be placed
        mCollapsed = new RelativeLayout(getBaseContext()); // Markup of the icon (when the menu is minimized)
        mExpanded = new LinearLayout(getBaseContext()); // Menu markup (when the menu is expanded)
                AssetManager assetManager = getAssets();
        view1 = new LinearLayout(getBaseContext());
        patches = new LinearLayout(getBaseContext());
                patches2 = new LinearLayout(getBaseContext());
        view2 = new LinearLayout(getBaseContext());
        mButtonPanel = new LinearLayout(getBaseContext()); // Layout of option buttons (when the menu is expanded)
                /*
                 Toast.makeText(this, (Html.fromHtml("AutoBypass Activated!!!!")), Toast.LENGTH_LONG).show();
                 Toast.makeText(this, (Html.fromHtml("Functions Will Load Soon After Bypass..........")), Toast.LENGTH_LONG).show();
                 */

        mButtonPanel = new LinearLayout(getBaseContext());
        rootFrame.setLayoutParams(new FrameLayout.LayoutParams(-1, -1));
                mRootContainer.setLayoutParams(new FrameLayout.LayoutParams(-2, -2));
                mCollapsed.setLayoutParams(new RelativeLayout.LayoutParams(-2, -2));
                mCollapsed.setVisibility(View.VISIBLE);

        // Create ImGui-style thin bar instead of image
        LinearLayout imguiBar = new LinearLayout(getBaseContext());
        LinearLayout.LayoutParams barParams = new LinearLayout.LayoutParams(dp(180), dp(28));
        barParams.topMargin = dp(15);
        imguiBar.setLayoutParams(barParams);
        imguiBar.setOrientation(LinearLayout.HORIZONTAL);
        imguiBar.setPadding(dp(8), dp(4), dp(8), dp(4));
        
        // ImGui bar background
        GradientDrawable barBg = new GradientDrawable();
        barBg.setColor(IMGUI_BG_DARK);
        barBg.setStroke(dp(1), IMGUI_BORDER);
        barBg.setCornerRadius(dp(4));
        imguiBar.setBackground(barBg);
        
        // DEXX-TER text
        TextView imguiTitle = new TextView(getBaseContext());
        LinearLayout.LayoutParams titleParams = new LinearLayout.LayoutParams(0, -2, 1f);
        imguiTitle.setLayoutParams(titleParams);
        imguiTitle.setText("DEXX-TER");
        imguiTitle.setTextColor(TEXT_COLOR);
        imguiTitle.setTextSize(12f);
        imguiTitle.setTypeface(null, Typeface.BOLD);
        imguiTitle.setGravity(Gravity.CENTER_VERTICAL);
        
        // Toggle button (▶)
        toggleBtn = new Button(getBaseContext());
        LinearLayout.LayoutParams btnParams = new LinearLayout.LayoutParams(dp(24), dp(20));
        toggleBtn.setLayoutParams(btnParams);
        toggleBtn.setText("▶");
        toggleBtn.setTextColor(IMGUI_ACCENT);
        toggleBtn.setTextSize(10f);
        toggleBtn.setPadding(0, 0, 0, 0);
        toggleBtn.setGravity(Gravity.CENTER);
        
        GradientDrawable btnBg = new GradientDrawable();
        btnBg.setColor(BTN_COLOR);
        btnBg.setCornerRadius(dp(2));
        toggleBtn.setBackground(btnBg);
        
        imguiBar.addView(imguiTitle);
        imguiBar.addView(toggleBtn);
        
        // Store reference for later access
        this.imguiBar = imguiBar;
        
        // Replace startimage reference
        startimage = new ImageView(getBaseContext());  // Keep for compatibility
        startimage.setLayoutParams(new LinearLayout.LayoutParams(0, 0));
        startimage.setVisibility(View.GONE);

        BadLogo2 = new ImageView(this);
        RelativeLayout.LayoutParams BadLogo2_LayoutParams = new RelativeLayout.LayoutParams(-0, -2);
        BadLogo2.setLayoutParams(new RelativeLayout.LayoutParams(-2, -2));
        BadLogo2_LayoutParams.addRule(0, -0);
        BadLogo2_LayoutParams.setMarginEnd((int) ((0.0f) + 0.0f));
        BadLogo2.getLayoutParams().height = dp(0);
        BadLogo2.getLayoutParams().width = dp(0);
        BadLogo2.requestLayout();
        InputStream inputStream_icone2 = null;
        try {
            inputStream_icone2 = assetManager.open("mrkiller2.5.png");
        } catch (IOException e) {
            e.printStackTrace();
        }
        Drawable icone2 = Drawable.createFromStream(inputStream_icone2, null);
        BadLogo2.setImageDrawable(icone2);
        ((ViewGroup.MarginLayoutParams) this.BadLogo2.getLayoutParams()).leftMargin = convertDipToPixels(0);


                mExpanded = new LinearLayout(this);
        mExpanded.setVisibility(View.GONE);
        mExpanded.setBackgroundColor(Color.rgb(0, 0, 0));
        mExpanded.setOrientation(1);
        mExpanded.setAlpha(0.95f);
        // ImGui-style expanded menu background
        GradientDrawable imguiMenuBg = new GradientDrawable();
        imguiMenuBg.setColor(IMGUI_BG_DARKER);
        imguiMenuBg.setStroke(dp(1), IMGUI_BORDER);
        imguiMenuBg.setCornerRadius(dp(6));
        mExpanded.setBackground(imguiMenuBg);
        mExpanded.setPadding(0, 0, 0, 0);
        mExpanded.setLayoutParams(new LinearLayout.LayoutParams(MENU_WIDTH, -2));


        // Create ImGui-style tab system
        createTabSystem();
        
        ScrollView scrollView = new ScrollView(this);
        scrollView.setLayoutParams(new LinearLayout.LayoutParams(-1, dp(185)));
        scrollView.addView(tabContent);

        // Remove legacy purple divider
        patches.setLayoutParams(new LinearLayout.LayoutParams(-1, -1));
        patches.setOrientation(1);
        patches2.setLayoutParams(new LinearLayout.LayoutParams(-1, -1));
        patches2.setOrientation(1);

        // Remove legacy purple divider

        mButtonPanel.setLayoutParams(new LinearLayout.LayoutParams(-2, -2));
        final ProgressBar Loading = new ProgressBar(this);
        TextView Bar = new TextView(this);
        TextView VersaoFF = new TextView(this);
        Loading.setForegroundGravity(Gravity.CENTER);
        Bar.append(new String(ForegroundGravity()));
        VersaoFF.append(new String(Gravity()));
        Loading.setPadding(0, 10, 0, 10);
        // Remove loading delay - create menu immediately
        Loading.setVisibility(View.GONE);
        CreateMenuList();

                LinearLayout title = new LinearLayout(this);
        // TextView View = new TextView(this);
        LinearLayout.LayoutParams layoutParams5 = new LinearLayout.LayoutParams(-2, -2);
        layoutParams5.gravity = 20;
        layoutParams5.leftMargin = dp(25);
        Bar.setTextSize(19.5f);
        Bar.setTextColor(IMGUI_ACCENT);
        title.setOrientation(0);
        title.setPadding(dp(15), dp(9), dp(9), dp(9));
        Bar.setTypeface(null, Typeface.BOLD_ITALIC);
        Bar.setLayoutParams(layoutParams5);
        title.setLayoutParams(new LinearLayout.LayoutParams(-1, -2));
        LinearLayout.LayoutParams VersaoFF2 = new LinearLayout.LayoutParams(-2, -2);

        VersaoFF.setTextColor(-1);
                VersaoFF.setTextSize(13.0f);
                VersaoFF.setTypeface((Typeface) null, 1);
                VersaoFF.setGravity(Gravity.CENTER);
        VersaoFF.setPadding(0,0,0,2);
            VersaoFF.setTextColor(Color.parseColor("blue"));


        RelativeLayout relativeLayout = new RelativeLayout(this);
        relativeLayout.setPadding(0, 0, 0, 0);
        relativeLayout.setLayoutParams(new RelativeLayout.LayoutParams(dp(-2), dp(33)));


        close = new Button(this);
        // ImGui-style close button
        close.setTextSize(11);
        close.setPadding(dp(8), dp(4), dp(8), dp(4));
        close.setText("CLOSE");
        close.setTextColor(TEXT_COLOR);
        GradientDrawable imguiCloseBg = new GradientDrawable();
        imguiCloseBg.setColor(BTN_COLOR);
        imguiCloseBg.setStroke(dp(1), IMGUI_BORDER);
        imguiCloseBg.setCornerRadius(dp(3));
        close.setBackground(imguiCloseBg);

        new LinearLayout.LayoutParams(-1, dp(25)).topMargin = dp(2);
        rootFrame.addView(mRootContainer);
        this.patches.addView(Loading);
        mRootContainer.addView(mCollapsed);
        mRootContainer.addView(mExpanded);
        mCollapsed.addView(imguiBar);
        mExpanded.addView(title);
        title.addView(BadLogo2);
        title.addView(Bar);
        mExpanded.addView(tabContainer);
        mExpanded.addView(scrollView);
        mExpanded.addView(VersaoFF);
        relativeLayout.addView(close);
        mFloatingView = rootFrame;
        mExpanded.addView(relativeLayout);

        if (Build.VERSION.SDK_INT >= 26) {
            params = new WindowManager.LayoutParams(-2, -2, 2038, 8, -3);
        } else {
            params = new WindowManager.LayoutParams(-2, -2, 2002, 8, -3);
        }

        WindowManager.LayoutParams layoutParams4 = params;
        layoutParams4.gravity = 51;
        layoutParams4.x = 0;
        layoutParams4.y = 50;
        mWindowManager = (WindowManager) getSystemService(Context.WINDOW_SERVICE);
        mWindowManager.addView(mFloatingView, params);
        RelativeLayout relativeLayout2 = mCollapsed;
        LinearLayout linearLayout = mExpanded;
        mFloatingView.setOnTouchListener(onTouchListener());
        imguiBar.setOnTouchListener(onTouchListener());
        // Don't add touch listener to toggleBtn to avoid click conflicts
        initMenuButton(relativeLayout2, linearLayout);
    }

    private View.OnTouchListener onTouchListener() {
        return new View.OnTouchListener() {
            final View collapsedView = mCollapsed;
            final View expandedView = mExpanded;
            private float initialTouchX;
            private float initialTouchY;
            private int initialX;
            private int initialY;
            public boolean onTouch(View view, MotionEvent motionEvent) {
                switch (motionEvent.getAction()) {
                    case MotionEvent.ACTION_DOWN:
                        initialX = params.x;
                        initialY = params.y;
                        initialTouchX = motionEvent.getRawX();
                        initialTouchY = motionEvent.getRawY();
                        return true;
                    case MotionEvent.ACTION_UP:
                        int rawX = (int) (motionEvent.getRawX() - initialTouchX);
                        int rawY = (int) (motionEvent.getRawY() - initialTouchY);
                        //The check for Xdiff <10 && YDiff< 10 because sometime elements moves a little while clicking.
                        //So that is click event.
                        if (rawX < 10 && rawY < 10 && isViewCollapsed()) {
                            //When user clicks on the image view of the collapsed layout,
                            //visibility of the collapsed layout will be changed to "View.GONE"
                            //and expanded view will become visible.
                            collapsedView.setVisibility(View.GONE);
                            expandedView.setVisibility(View.VISIBLE);
                            //Toast.makeText(FloatingModMenuService.this, Html.fromHtml(Toast()), Toast.LENGTH_SHORT).show();
                        }
                        return true;
                    case MotionEvent.ACTION_MOVE:
                        //Calculate the X and Y coordinates of the view.
                        params.x = initialX + ((int) (motionEvent.getRawX() - initialTouchX));
                        params.y = initialY + ((int) (motionEvent.getRawY() - initialTouchY));
                        //Update the layout with new X & Y coordinate
                        mWindowManager.updateViewLayout(mFloatingView, params);
                        return true;
                    default:
                        return false;
                }
            }
        };
    }

        private boolean hide = false;
    private void initMenuButton(final View view2, final View view3) {
        // ImGui-style toggle button click handler
        toggleBtn.setOnClickListener(new View.OnClickListener() {
                public void onClick(View view) {
                    if (view3.getVisibility() == View.GONE) {
                        // Currently collapsed, expand the menu
                        view2.setVisibility(View.GONE);
                        view3.setVisibility(View.VISIBLE);
                        toggleBtn.setText("▼");
                    } else {
                        // Currently expanded, collapse the menu
                        view2.setVisibility(View.VISIBLE);
                        view3.setVisibility(View.GONE);
                        toggleBtn.setText("▶");
                    }
                }
            });
                close.setOnClickListener(new View.OnClickListener() {
                                public void onClick(View view) {
                                        if (hide) {
                                                view2.setVisibility(View.VISIBLE);
                                                view2.setAlpha(0);
                                                view3.setVisibility(View.GONE);
                                        } else {
                                                view2.setVisibility(View.VISIBLE);
                                                view2.setAlpha(0.95f);
                                                view3.setVisibility(View.GONE);
                                        }
                                }
                        });
    }

    private void createTabSystem() {
        // Create tab container
        tabContainer = new LinearLayout(this);
        tabContainer.setLayoutParams(new LinearLayout.LayoutParams(-1, dp(35)));
        tabContainer.setOrientation(LinearLayout.HORIZONTAL);
        tabContainer.setPadding(dp(4), dp(4), dp(4), dp(4));
        
        // Create tab buttons
        aimTab = createTabButton("AIM", 0);
        espTab = createTabButton("ESP", 1);
        brutalTab = createTabButton("BRUTAL", 2);
        otherTab = createTabButton("OTHER", 3);
        
        tabContainer.addView(aimTab);
        tabContainer.addView(espTab);
        tabContainer.addView(brutalTab);
        tabContainer.addView(otherTab);
        
        // Create content container
        tabContent = new LinearLayout(this);
        tabContent.setLayoutParams(new LinearLayout.LayoutParams(-1, -1));
        tabContent.setOrientation(LinearLayout.VERTICAL);
        
        // Create individual tab content containers
        aimContent = new LinearLayout(this);
        aimContent.setLayoutParams(new LinearLayout.LayoutParams(-1, -2));
        aimContent.setOrientation(LinearLayout.VERTICAL);
        
        espContent = new LinearLayout(this);
        espContent.setLayoutParams(new LinearLayout.LayoutParams(-1, -2));
        espContent.setOrientation(LinearLayout.VERTICAL);
        
        brutalContent = new LinearLayout(this);
        brutalContent.setLayoutParams(new LinearLayout.LayoutParams(-1, -2));
        brutalContent.setOrientation(LinearLayout.VERTICAL);
        
        otherContent = new LinearLayout(this);
        otherContent.setLayoutParams(new LinearLayout.LayoutParams(-1, -2));
        otherContent.setOrientation(LinearLayout.VERTICAL);
        
        // Set AIM tab as default active
        switchToTab(0);
    }
    
    private Button createTabButton(String text, final int tabIndex) {
        Button tabBtn = new Button(this);
        LinearLayout.LayoutParams params = new LinearLayout.LayoutParams(0, dp(27), 1f);
        params.setMargins(dp(1), 0, dp(1), 0);
        tabBtn.setLayoutParams(params);
        tabBtn.setText(text);
        tabBtn.setTextSize(9f);
        tabBtn.setTextColor(TEXT_COLOR_2);
        tabBtn.setPadding(0, 0, 0, 0);
        
        // ImGui tab styling
        GradientDrawable tabBg = new GradientDrawable();
        tabBg.setColor(BTN_COLOR);
        tabBg.setStroke(dp(1), IMGUI_BORDER);
        tabBg.setCornerRadius(dp(2));
        tabBtn.setBackground(tabBg);
        
        tabBtn.setOnClickListener(new View.OnClickListener() {
            public void onClick(View v) {
                switchToTab(tabIndex);
            }
        });
        
        return tabBtn;
    }
    
    private void switchToTab(int tabIndex) {
        currentTab = tabIndex;
        
        // Update tab button styles
        resetTabButtons();
        Button activeTab = null;
        switch(tabIndex) {
            case 0: activeTab = aimTab; break;
            case 1: activeTab = espTab; break;
            case 2: activeTab = brutalTab; break;
            case 3: activeTab = otherTab; break;
        }
        
        if (activeTab != null) {
            GradientDrawable activeBg = new GradientDrawable();
            activeBg.setColor(IMGUI_ACCENT);
            activeBg.setStroke(dp(1), IMGUI_BORDER);
            activeBg.setCornerRadius(dp(2));
            activeTab.setBackground(activeBg);
            activeTab.setTextColor(TEXT_COLOR);
        }
        
        // Switch content
        tabContent.removeAllViews();
        switch(tabIndex) {
            case 0: tabContent.addView(aimContent); break;
            case 1: tabContent.addView(espContent); break;
            case 2: tabContent.addView(brutalContent); break;
            case 3: tabContent.addView(otherContent); break;
        }
    }
    
    private void resetTabButtons() {
        Button[] tabs = {aimTab, espTab, brutalTab, otherTab};
        for (Button tab : tabs) {
            GradientDrawable tabBg = new GradientDrawable();
            tabBg.setColor(BTN_COLOR);
            tabBg.setStroke(dp(1), IMGUI_BORDER);
            tabBg.setCornerRadius(dp(2));
            tab.setBackground(tabBg);
            tab.setTextColor(TEXT_COLOR_2);
        }
    }

    private void CreateMenuList() {
        String[] listFT = getFeatureList();
        
        // Clear all tab contents first
        aimContent.removeAllViews();
        espContent.removeAllViews();
        brutalContent.removeAllViews();
        otherContent.removeAllViews();
        
        for (int i = 0; i < listFT.length; i++) {
            final int feature = i;
            String str = listFT[i];
            
            // Skip category headers (CT_) as we organize by tabs now
            if (str.contains("CT_")) {
                continue;
            }
            
            // Determine which tab this function belongs to
            LinearLayout targetContainer = getTargetContainer(str);
            
            if (str.contains("Toggle55_")) {
                addButtonToTab(targetContainer, str.replace("Toggle55_", ""), new InterfaceBtn() {
                    public void OnWrite() {
                        Changes(feature, 0);
                    }
                });
            } else if (str.contains("Toggle2_")) {
                addButtonToTab(targetContainer, str.replace("Toggle2_", ""), new InterfaceBtn() {
                    public void OnWrite() {
                        Changes(feature, 0);
                    }
                });
            } else if (str.contains("Toggle_")) {
                addButtonToTab(targetContainer, str.replace("Toggle_", ""), new InterfaceBtn() {
                    public void OnWrite() {
                        Changes(feature, 0);
                    }
                });
            } else if (str.contains("SB_")) {
                String[] split = str.split("_");
                addSeekbarToTab(targetContainer, split[1], Integer.parseInt(split[2]), Integer.parseInt(split[3]), new InterfaceInt() {
                    public void OnWrite(int i) {
                        Changes(feature, i);
                    }
                });
            }
        }
    }
    
    private LinearLayout getTargetContainer(String featureName) {
        String name = featureName.toUpperCase();
        
        // AIM tab functions
        if (name.contains("AIM") || name.contains("SPEED") || name.contains("FOV") || name.contains("FIRE") || name.contains("SCOPE") || name.contains("VISBEL") || name.contains("MOVEMENT")) {
            return aimContent;
        }
        
        // ESP tab functions  
        if (name.contains("ESP")) {
            return espContent;
        }
        
        // BRUTAL tab functions (destructive/powerful hacks)
        if (name.contains("FLY") || name.contains("TELEKILL") || name.contains("TELEPORT") || name.contains("GHOST")) {
            return brutalContent;
        }
        
        // Everything else goes to OTHER tab
        return otherContent;
    }
    
    private void addButtonToTab(LinearLayout container, String feature, final InterfaceBtn interfaceBtn) {
        final Button button = new Button(this);
        LinearLayout.LayoutParams layoutParams = new LinearLayout.LayoutParams(-1, dp(32));
        layoutParams.setMargins(dp(4), dp(2), dp(4), dp(2));
        button.setLayoutParams(layoutParams);
        button.setPadding(dp(8), dp(4), dp(8), dp(4));
        button.setTextSize(10.0f);
        button.setTextColor(TEXT_COLOR);
        button.setTypeface(Typeface.DEFAULT);
        button.setGravity(Gravity.CENTER);
        
        // ImGui-style button setup
        button.setText(feature + " OFF");
        GradientDrawable buttonBg = new GradientDrawable();
        buttonBg.setColor(BTN_COLOR);
        buttonBg.setStroke(dp(1), IMGUI_BORDER);
        buttonBg.setCornerRadius(dp(3));
        button.setBackground(buttonBg);
        
        button.setOnClickListener(new View.OnClickListener() {
            boolean isOn = false;
            public void onClick(View view) {
                isOn = !isOn;
                if (isOn) {
                    button.setText(feature + " ON");
                    GradientDrawable activeBg = new GradientDrawable();
                    activeBg.setColor(IMGUI_ACCENT);
                    activeBg.setStroke(dp(1), IMGUI_BORDER);
                    activeBg.setCornerRadius(dp(3));
                    button.setBackground(activeBg);
                } else {
                    button.setText(feature + " OFF");
                    GradientDrawable inactiveBg = new GradientDrawable();
                    inactiveBg.setColor(BTN_COLOR);
                    inactiveBg.setStroke(dp(1), IMGUI_BORDER);
                    inactiveBg.setCornerRadius(dp(3));
                    button.setBackground(inactiveBg);
                }
                interfaceBtn.OnWrite();
            }
        });
        
        container.addView(button);
    }
    
    private void addSeekbarToTab(LinearLayout container, String text, int min, int max, final InterfaceInt interfaceInt) {
        LinearLayout seekLayout = new LinearLayout(this);
        seekLayout.setLayoutParams(new LinearLayout.LayoutParams(-1, dp(40)));
        seekLayout.setOrientation(LinearLayout.VERTICAL);
        seekLayout.setPadding(dp(8), dp(4), dp(8), dp(4));
        
        TextView label = new TextView(this);
        label.setText(text + ": " + min);
        label.setTextColor(TEXT_COLOR);
        label.setTextSize(9f);
        
        SeekBar seekBar = new SeekBar(this);
        seekBar.setMax(max - min);
        seekBar.setProgress(0);
        
        // ImGui-style seekbar
        seekBar.setOnSeekBarChangeListener(new SeekBar.OnSeekBarChangeListener() {
            public void onProgressChanged(SeekBar seekBar, int progress, boolean fromUser) {
                int value = min + progress;
                label.setText(text + ": " + value);
                interfaceInt.OnWrite(value);
            }
            public void onStartTrackingTouch(SeekBar seekBar) {}
            public void onStopTrackingTouch(SeekBar seekBar) {}
        });
        
        seekLayout.addView(label);
        seekLayout.addView(seekBar);
        container.addView(seekLayout);
    }

    private TextView textView2;
    private String featureNameExt;
    private int featureNum;
    private EditTextValue txtValue;

    public class EditTextValue {
        private int val;

        public void setValue(int i) {
            val = i;
        }

        public int getValue() {
            return val;
        }
    }

        private void addCategory(String text) {
        TextView textView = new TextView(this);
        LinearLayout.LayoutParams layoutParams7 = new LinearLayout.LayoutParams(-1, -2);
        textView.setText(text);
        layoutParams7.setMargins(15, 3, 15, 3);
        textView.setLayoutParams(layoutParams7);
        textView.setPadding(5, 5, 5, 5);
        textView.setTextSize(11);
                textView.setTextColor(Color.parseColor( "#FF0004"));
        textView.setGravity(17);
                textView.setBackgroundColor(Color.parseColor( "#FFF800"));
        patches.addView(textView);
    }


    public void addButton(String feature, final InterfaceBtn interfaceBtn) {
        final Button button = new Button(this);
        LinearLayout.LayoutParams layoutParams = new LinearLayout.LayoutParams(-1, dp(40));
        layoutParams.setMargins(15, 3, 15, 3);
        button.setLayoutParams(layoutParams);
        button.setPadding(5, 5, 5, 5);
        button.setTextSize(13.0f);
        button.setTextColor(Color.parseColor("WHITE"));
        button.setTypeface(Typeface.DEFAULT);
        button.setAlpha(9.99f);
        button.setGravity(17);
        if (feature.contains("")) {
            feature = feature.replace("", "");
            //button.setText(Html.fromHtml("" + feature + " OFF" + "</font>"));
            button.setText(Html.fromHtml("<font>" + feature + " <font color='WHITE'>" + "OFF" + "</font>"));
            button.setBackgroundColor(Color.TRANSPARENT);
            android.graphics.drawable.GradientDrawable GAFDJHE = new android.graphics.drawable.GradientDrawable();
            GAFDJHE.setColor(Color.parseColor("Black"));
                        GAFDJHE.setStroke(6, Color.parseColor("#FFF800"));
            GAFDJHE.setCornerRadius(10);
            android.graphics.drawable.RippleDrawable GAFDJHE_RE = new android.graphics.drawable.RippleDrawable(new android.content.res.ColorStateList(new int[][]{new int[]{}}, new int[]{ Color.parseColor("Black")}), GAFDJHE, null);
            button.setBackground(GAFDJHE_RE);
            if(Build.VERSION.SDK_INT >= 21) {
                button.setElevation(5f); }
            final String feature2 = feature;
            button.setOnClickListener(new View.OnClickListener() {
                    private boolean isActive = true;
                    public void onClick(View v) {
                        interfaceBtn.OnWrite();
                        if (isActive) {
                            //button.setText(Html.fromHtml("" + feature2 + " ON" + "</font>"));
                            button.setText(Html.fromHtml("<font>" + feature2 + " <font color='WHITE'>" + "ON" + "</font>"));
                            android.graphics.drawable.GradientDrawable ICECHHF = new android.graphics.drawable.GradientDrawable();
                            ICECHHF.setColor(Color.argb(250, 10, 140, 180));
                                                        ICECHHF.setColor(Color.parseColor("blue"));
                                                        ICECHHF.setStroke(6, Color.parseColor("#FFF800"));
                                                        button.setBackgroundColor(Color.TRANSPARENT);
                            ICECHHF.setCornerRadius(10);
                            android.graphics.drawable.RippleDrawable ICECHHF_RE = new android.graphics.drawable.RippleDrawable(new android.content.res.ColorStateList(new int[][]{new int[]{}}, new int[]{ Color.parseColor("black")}), ICECHHF, null);
                            button.setBackground(ICECHHF_RE);
                            if(Build.VERSION.SDK_INT >= 21) {
                                button.setElevation(5f); }
                            isActive = false;
                            return;
                        }
                        //button.setText(Html.fromHtml("" + feature2 + " OFF" + "</font>"));
                        button.setText(Html.fromHtml("<font>" + feature2 + " <font color='WHITE'>" + "OFF" + "</font>"));
                        button.setBackgroundColor(Color.TRANSPARENT);
                        android.graphics.drawable.GradientDrawable GAFDJHE = new android.graphics.drawable.GradientDrawable();
                        GAFDJHE.setColor(Color.parseColor("Black"));
                                                GAFDJHE.setStroke(6, Color.parseColor("#FFF800"));
                        GAFDJHE.setCornerRadius(10);
                        android.graphics.drawable.RippleDrawable GAFDJHE_RE = new android.graphics.drawable.RippleDrawable(new android.content.res.ColorStateList(new int[][]{new int[]{}}, new int[]{ Color.parseColor("red")}), GAFDJHE, null);
                        button.setBackground(GAFDJHE_RE);
                        if(Build.VERSION.SDK_INT >= 21) {
                            button.setElevation(5f); }
                        isActive = true;
                    }
                });
        } else {
            button.setText(feature);
            button.setAlpha(9.99f);
            button.setBackgroundColor(Color.TRANSPARENT);
            final String feature2 = feature;
            button.setOnClickListener(new View.OnClickListener() {
                    public void onClick(View v) {
                        interfaceBtn.OnWrite();
                        button.setAlpha(9.99f);
                    }
                });
        }
        patches.addView(button);
    }

        public void addButtonm(String feature, final InterfaceBtn interfaceBtn) {
        final TextView button = new TextView(this);
        LinearLayout.LayoutParams layoutParams = new LinearLayout.LayoutParams(-1, dp(35));
        layoutParams.setMargins(4, 2, 4, 2);
        button.setLayoutParams(layoutParams);
        button.setTextSize(11);
        button.setTextColor(-1);
        button.setGravity(17);
        GradientDrawable gradienteOff = new GradientDrawable();
        gradienteOff.setShape(0);
        gradienteOff.setStroke(5, Color.parseColor("#000000"));
        gradienteOff.setColor(Color.parseColor("#000000"));
        gradienteOff.setCornerRadii(new float[] { 40, 40, 40, 40, 80, 80, 80, 80 });
        /*if (Build.VERSION.SDK_INT >= 21) {
                 button.setElevation(90.0f);
                 }*/
        final GradientDrawable gradientDrawable = gradienteOff;
        final RippleDrawable GIDDGID_RE = new RippleDrawable(new ColorStateList(new int[][]{new int[]{}}, new int[]{ Color.RED}), gradienteOff, null);
        gradientDrawable.setOrientation(GradientDrawable.Orientation.TL_BR);
        button.setBackground(GIDDGID_RE);
        button.setTypeface((Typeface) null, 1);
        if (feature.contains("")) {
            feature = feature.replace("", "");
            button.setText(feature);
            final String feature2 = feature;
            button.setOnClickListener(new View.OnClickListener() {
                    private boolean isActive = true;
                    public void onClick(View v) {
                        interfaceBtn.OnWrite();
                        if (isActive) {
                            button.setText(feature2);
                            isActive = false;
                            GradientDrawable gradienteOn = new GradientDrawable();
                            gradienteOn.setShape(0);
                            gradienteOn.setStroke(5, Color.parseColor("#000000"));
                            gradienteOn.setColor(Color.parseColor("#000000"));
                            RippleDrawable GIDDGID_RE2 = new RippleDrawable(new ColorStateList(new int[][]{new int[]{}}, new int[]{ Color.RED}), gradienteOn, null);
                            gradienteOn.setCornerRadii(new float[] { 40, 40, 40, 40, 80, 80, 80, 80 });
                            /*if (Build.VERSION.SDK_INT >= 21) {
                                                         button.setElevation(90.0f);
                                                         }*/
                            button.setBackground(GIDDGID_RE2);
                            return;
                        }
                        button.setText(feature2);
                        isActive = true;
                        GradientDrawable gradienteOff = new GradientDrawable();
                        gradienteOff.setShape(0);
                        gradienteOff.setStroke(5, Color.parseColor("#000000"));
                        gradienteOff.setColor(Color.parseColor("#000000"));
                        gradienteOff.setCornerRadii(new float[] { 40, 40, 40, 40, 80, 80, 80, 80 });

                        /*if (Build.VERSION.SDK_INT >= 21) {
                                                 button.setElevation(90.0f);
                                                 }*/
                        final GradientDrawable gradientDrawable = gradienteOff;
                        final RippleDrawable GIDDGID_RE = new RippleDrawable(new ColorStateList(new int[][]{new int[]{}}, new int[]{ Color.RED}), gradienteOff, null);
                        gradientDrawable.setOrientation(GradientDrawable.Orientation.TL_BR);
                        button.setBackground(GIDDGID_RE);
                    }
                });
        } else {
            button.setText(feature);

            final String feature2 = feature;
            button.setBackground(gradientDrawable);
            button.setOnClickListener(new View.OnClickListener() {
                    public void onClick(View v) {
                        interfaceBtn.OnWrite();

                    }
                });
        }
        patches.addView(button);
    }

        public void addButton1(String feature, final InterfaceBtn interfaceBtn) {
                final Button button = new Button(this);
                LinearLayout.LayoutParams layoutParams = new LinearLayout.LayoutParams(-1, dp(35));
                layoutParams.setMargins(4, 2, 4, 2);
                button.setLayoutParams(layoutParams);
                button.setTextSize(11);
                button.setBackground(Preferences.bbbbb_aaaaaaaa(this));
                button.setTextColor(-1);
                button.setGravity(17);
                button.setTypeface((Typeface) null, 1);
                if (feature.contains("")) {
                        feature = feature.replace("", "");
                        button.setText(feature + " ON");
                        final String feature2 = feature;
                        button.setOnClickListener(new View.OnClickListener() {
                                        private boolean isActive = true;
                                        public void onClick(View v) {
                                                interfaceBtn.OnWrite();
                                                if (isActive) {
                                                        button.setText(feature2 + " OFF");
                                                        isActive = false;
                                                        //Toast.makeText(ctx, Html.fromHtml(feature2 + "<font color='GREEN'>"+" ON</font>"), Toast.LENGTH_SHORT).show();
                                                        button.setBackground(Preferences.botoes(getBaseContext()));
                                                        return;
                                                }
                                                button.setText(feature2 + " ON");
                                                isActive = true;
                                                //Toast.makeText(ctx, Html.fromHtml(feature2 + "<font color='GREEN'>"+" OFF</font>"), Toast.LENGTH_SHORT).show();
                                                button.setBackground(Preferences.bbbbb_aaaaaaaa(getBaseContext()));
                                        }
                                });
                } else {
                        button.setText(feature);
                        final String feature2 = feature;
                        button.setBackground(Preferences.botoes(this));
                        button.setOnClickListener(new View.OnClickListener() {
                                        public void onClick(View v) {
                                                interfaceBtn.OnWrite();
                                        }
                                });
                }
                patches.addView(button);
        }



        private void addSeekbarFly(final String feature, final int prog, int max, final InterfaceInt interInt) {
        LinearLayout linearLayout = new LinearLayout(this);
        LinearLayout.LayoutParams layoutParams = new LinearLayout.LayoutParams(-1, -1);
        linearLayout.setPadding(10, 5, 0, 5);
        linearLayout.setOrientation(LinearLayout.VERTICAL);
        linearLayout.setGravity(18);
        linearLayout.setLayoutParams(layoutParams);
        linearLayout.setBackgroundColor(Color.TRANSPARENT);
        LinearLayout view4 = new LinearLayout(this);
        view4.setLayoutParams(new LinearLayout.LayoutParams(-1, 2));
        LinearLayout view5 = new LinearLayout(this);
        view5.setLayoutParams(new LinearLayout.LayoutParams(-1, 2));
        final TextView textView = new TextView(this);
        textView.setText(Html.fromHtml("" + feature + " : <font color='WHITE'>" + "0x" + "</font>"));
        textView.setTextColor(Color.WHITE);
        textView.setTextSize(11.5f);
        SeekBar seekBar = new SeekBar(this);
        seekBar.setLayoutParams(new LinearLayout.LayoutParams(-1, -1));
                seekBar.getThumb().setColorFilter(Color.parseColor("BLUE"), PorterDuff.Mode.SRC_IN);
        seekBar.setMax(max);
        seekBar.setProgress(prog);
        final TextView textView2 = textView;
        seekBar.getProgressDrawable().setColorFilter(Color.parseColor("#FFF800"), PorterDuff.Mode.MULTIPLY);
        seekBar.getThumb().setColorFilter(Color.parseColor("blue"), PorterDuff.Mode.SRC_IN);
        seekBar.setOnSeekBarChangeListener(new SeekBar.OnSeekBarChangeListener() {
                public void onStartTrackingTouch(SeekBar seekBar) {
                }
                public void onStopTrackingTouch(SeekBar seekBar) {
                }
                int l;
                public void onProgressChanged(SeekBar seekBar, int i, boolean z) {
                    if (i == 0) {
                        seekBar.setProgress(i);
                        interInt.OnWrite(i);
                        TextView textView = textView2;
                        textView.setText(Html.fromHtml("" + feature + " : <font color='WHITE'>" + "0x" + "</font>"));

                        return;
                    }
                    interInt.OnWrite(i);
                    textView.setText(Html.fromHtml("" + feature + " : <font color='WHITE'>" + i + "x</font>"));

                }
            });

        linearLayout.addView(textView);
        linearLayout.addView(seekBar);
        patches.addView(linearLayout);
    }





    boolean delayed;

    public boolean isViewCollapsed() {
        return mFloatingView == null || mCollapsed.getVisibility() == View.VISIBLE;
    }

    private int convertDipToPixels(int i) {
        return (int) ((((float) i) * getResources().getDisplayMetrics().density) + 0.5f);
    }

    private int dp(int i) {
        return (int) TypedValue.applyDimension(1, (float) i, getResources().getDisplayMetrics());
    }

    public void onDestroy() {
        super.onDestroy();
        if (view2 != null) {
            this.mWindowManager.removeView(view2);
        }
        View view = mFloatingView;
        if (view != null) {
            mWindowManager.removeView(view);
        }
    }

    private boolean isNotInGame() {
        RunningAppProcessInfo runningAppProcessInfo = new RunningAppProcessInfo();
        ActivityManager.getMyMemoryState(runningAppProcessInfo);
        return runningAppProcessInfo.importance != 100;
    }

    private interface InterfaceBtn {
        void OnWrite();
    }

    private interface InterfaceInt {
        void OnWrite(int i);
    }

    private interface InterfaceBool {
        void OnWrite(boolean z);
    }

    private interface InterfaceStr {
        void OnWrite(String s);
    }
}

