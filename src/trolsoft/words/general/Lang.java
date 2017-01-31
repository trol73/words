package trolsoft.words.general;

public enum Lang {
	English("en", "English"),
	German("de", "Deutsch"),
	Russian("ru", "Русский"),
	French("fr", "Français"),
	Chinese("zh", "中文"),
	Italian("it", "Italiano"),
	Japanese("ja", "日本語"),
	Korean("ko", "한국어"),
	Portuguese("pt", "Português"),
	Spanish("es", "Español");
	
	
	private final String shortName;
	private final String nativeName;
	
	Lang(String shortName, String nativeName) {
		this.shortName = shortName;
		this.nativeName = nativeName;
	}
	
	
	public String getShortName() {
		return shortName;
	}
	
	public String getNativeName() {
		return nativeName;
	}

}
