package converter;

import java.util.MissingResourceException;
import java.util.ResourceBundle;

/**
 * @author tlroche
 * @version $Id: CelsiusConverterStrings.java,v 1.2 2004/12/31 04:49:48 tlroche Exp $
 */
public class CelsiusConverterStrings {
	private static final String BUNDLE_NAME = "converter.CelsiusConverter";//$NON-NLS-1$

	private static final ResourceBundle RESOURCE_BUNDLE = ResourceBundle
			.getBundle(BUNDLE_NAME);

	private CelsiusConverterStrings() {
	}

	public static String getString(String key) {
		try {
			return RESOURCE_BUNDLE.getString(key);
		} catch (MissingResourceException e) {
			return '!' + key + '!';
		}
	}
}
